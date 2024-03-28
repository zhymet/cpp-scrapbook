#pragma once
#include <iostream>
#include <string_view>
#include <string>
#include <array>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include "caf_debug.hpp"

namespace caf {
    class resource_manager {
    private:
        struct resource {
            std::string name;
            std::string ext;
            std::string path;
            std::string tag;
        };
    public:
        std::vector<resource> resources;

        void load_folder(const std::string& path, const std::string& tag, const std::string& extension) {
            int index = 0;
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                if (std::filesystem::is_regular_file(entry)) {
                    if (entry.path().extension().string() == extension) {
                        auto existingResource = std::find_if(resources.begin(), resources.end(),
                            [&tag](const resource& res) { return res.tag == tag; });

                        if (existingResource != resources.end()) {
                            // Resource with the same tag already exists, replace it
                            *existingResource = {
                                entry.path().filename().string().c_str(),
                                entry.path().extension().string().c_str(),
                                entry.path().string().c_str(),
                                tag + std::to_string(index)
                            };
                            debug::debug_logger.log_print("Replaced File: " + entry.path().string() + " | File Tag:" + tag + std::to_string(index));
                        }
                        else {
                            // Add a new resource
                            resources.push_back({
                                entry.path().filename().string().c_str(),
                                entry.path().extension().string().c_str(),
                                entry.path().string().c_str(),
                                tag + std::to_string(index)
                                });
                            debug::debug_logger.log_print("Loaded File: " + entry.path().string() + " | File Tag:" + tag + std::to_string(index));
                        }

                        index++;
                    }
                }
            }
        }

        void load_file(const std::string& fileName, const std::string& tag) {
            auto existingResource = std::find_if(resources.begin(), resources.end(),
                [&tag](const resource& res) { return res.tag == tag; });

            if (existingResource != resources.end()) {
                // Resource with the same tag already exists, replace it
                *existingResource = {
                    std::filesystem::path(fileName).filename().string().c_str(),
                    std::filesystem::path(fileName).extension().string().c_str(),
                    std::filesystem::path(fileName).string().c_str(),
                    tag
                };
                debug::debug_logger.log_print("Replaced File: " + fileName + " | File Tag:" + tag);
            }
            else {
                // Add a new resource
                resources.push_back({
                    std::filesystem::path(fileName).filename().string().c_str(),
                    std::filesystem::path(fileName).extension().string().c_str(),
                    std::filesystem::path(fileName).string().c_str(),
                    tag
                    });
                debug::debug_logger.log_print("Loaded File: " + fileName + " | File Tag:" + tag);
            }
        }

        const resource& get(const std::string& tag) const {
            auto foundResource = std::find_if(resources.begin(), resources.end(),
                [&tag](const resource& res) { return res.tag == tag; });

            // If the tag is not found, you might want to handle this case accordingly.
            // For now, I'm returning the first resource in the vector as a placeholder.
            return (foundResource != resources.end()) ? *foundResource : resources.front();
        }
    };
};