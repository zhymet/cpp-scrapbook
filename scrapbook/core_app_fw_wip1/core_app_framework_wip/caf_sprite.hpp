//#pragma once
//#include "vec2.hpp"
//#include <vector>
//#include <array>
//#include <cassert>
//#include <iterator>
//#include "caf_debug.hpp"
//namespace caf {
//
//    //TODO: Replace with more generic bounding box
//    struct Frame {
//        gtl::vec2<float> pos{ 0.f,0.f };
//        gtl::vec2<float> size{ 0.f,0.f };
//        constexpr gtl::vec2<float> aspect_ratio() {
//            return size.normalized(); // Get the unit vector of the sprite size
//        }
//
//        Frame() = default;
//        Frame(float posx, float posy, float sizex, float sizey) : pos(posx,posy),size(sizex,sizey){}
//    };
//
//    class spritesheet {
//        gtl::vec2<float> map_size_{ 0.f,0.f };
//        const std::vector<Frame> * frames_; // Pos and size of frame on the texture map
//        const std::vector<std::vector<size_t>> * animations_;
//    public:
//        spritesheet(const std::vector<Frame>& frames, const std::vector<std::vector<size_t>>& animations,
//            float sizex = 0.f, float sizey = 0.f) : frames_(&frames),map_size_(sizex, sizey), animations_(&animations) {}
//
//        void setFrames(const std::vector<Frame>& a_spritesheet) { frames_ = &a_spritesheet; }
//        void setAnimations(const std::vector<std::vector<size_t>> & animations) { animations_ = &animations; }
//        const std::vector<Frame>& getSpritesheet() const { return *frames_; }
//        const std::vector<std::vector<size_t> >& getAnimations() const { return *animations_; }
//
//        // Returns the texture co-ordinates to be used by OpenGl to render the sub texture.
//        constexpr std::array<gtl::Vec2f, 4> getFrameUV(std::vector<Frame>::const_iterator frame_it) const {
//            const auto& frame = *frame_it;
//            return {
//                // Top Right of Texture Bounds
//                gtl::Vec2f{(frame.size.x + frame.pos.x) / map_size_.x,(frame.pos.y + frame.size.y) / map_size_.y}
//                // Bottom Right of Texture Bounds
//                ,gtl::Vec2f{(frame.size.x + frame.pos.x) / map_size_.x,frame.pos.y / map_size_.x}
//                // Bottom Left of Texture Bounds
//                ,gtl::Vec2f{frame.pos.x / map_size_.x,frame.pos.y / map_size_.y}
//                // Top Left of Texture Bounds
//                ,gtl::Vec2f{frame.pos.x / map_size_.x,(frame.pos.y + frame.size.y) / map_size_.y} };
//        }
//
//        // Returns the texture co-ordinates to be used by OpenGl to render the sub texture as a raw array x,y
//        constexpr std::array<float, 8> getFrameUVRaw(std::vector<Frame>::const_iterator frame_it) const {
//            const auto& frame = *frame_it;
//            return {
//                // Top Right of Texture Bounds
//                (frame.size.x + frame.pos.x) / map_size_.x,
//                (frame.pos.y + frame.size.y) / map_size_.y,
//                // Bottom Right of Texture Bounds
//                (frame.size.x + frame.pos.x) / map_size_.x,
//                frame.pos.y / map_size_.x,
//                // Bottom Left of Texture Bounds
//                frame.pos.x / map_size_.x,
//                frame.pos.y / map_size_.y,
//                // Top Left of Texture Bounds
//                frame.pos.x / map_size_.x,
//                (frame.pos.y + frame.size.y) / map_size_.y };
//        }
//
//    };
//
//
//    // TO DO: Make sure that the source spritesheet is not a null pointer, if it is then handle it appropriatley
//    class sprite {
//        size_t active_frame_;
//        size_t active_animation_;
//        size_t init_frame_ = 0; // Initial frame of active animation, loop restarts from this frame, 0(first frame) by default
//        const spritesheet *  source_spritesheet;
//    public:
//        std::vector<std::vector<size_t>> animations_; // A list of animations
//
//        void addAnimation(std::vector<size_t> frame_indices) { animations_.push_back({ frame_indices }); }
//
//        void setSpritesheet(const spritesheet& a_spritesheet) { source_spritesheet = &a_spritesheet; }
//        void setActiveAnimation(size_t anim_idx, size_t init_frame) {
//            active_frame_ = init_frame;
//            active_animation_ = anim_idx;
//        };
//        void setActiveFrame(size_t active_frame) {
//            active_frame_ = active_frame;
//        };
//        void setInitFrame(size_t init_frame){ init_frame_ = init_frame; }
//
//        void nextFrame() {
//            if (active_frame_ >= animations_.at(active_animation_).size()) {
//                active_frame_ = init_frame_; // Reset back to init frame after last frame
//            }
//            else {
//                active_frame_++; // Active frame is the next one
//            }
//        };
//
//        const spritesheet & getActiveSpritesheet() { 
//            //assert(source_spritesheet && "getActiveSpritesheet must not be called before a spritesheet is set.");
//            return *source_spritesheet; 
//        }
//        size_t getActiveAnimation() { return active_animation_; }
//        std::vector<Frame>::const_iterator getActiveFrame() {
//           // assert(source_spritesheet && "getActiveFrame must not be called before a spritesheet is set.");
//            // Check if source_spritesheet has frames
//            if (getActiveSpritesheet().getSpritesheet()->empty()) {
//                // Handle the case where there are no frames (you might want to throw an exception or return a default frame)
//                debug::debug_logger.log_print("Error: No frames in the spritesheet.");
//                // Assuming you have some default frame or you might throw an exception
//                // returning the first frame as a placeholder
//                return source_spritesheet->frames_.begin();
//            }
//
//            // If active frame index is higher than the amount of frames, it will wrap around to the beginning
//            size_t index = active_frame_ % source_spritesheet->frames_.size();
//
//            auto active_frame = source_spritesheet->frames_.begin();
//            std::advance(active_frame, index);
//            return active_frame;
//        }
//        size_t getActiveFrameIndex() { return active_frame_; }
//        std::array<gtl::Vec2f, 4> getActiveFrameUV(){
//            return source_spritesheet->get_frame_uv(getActiveFrame());
//        };
//        std::array<float, 8> getActiveFrameUVRaw() {
//            return source_spritesheet->get_frame_uv_raw(getActiveFrame());
//        };
//
//    };
//
//
//};
////
////class Sprite
////{
////
////private:
////    std::vector<std::vector<size_t>> animations_; // A list animations
////    std::vector<Frame> frames_; // Pos and size of frame on the texture map
////    gtl::vec2<float> map_size_{ 0.f,0.f };
////    size_t active_frame_;
////    size_t active_animation_;
////    size_t init_frame_ = 0; // Initial frame of active animation, loop restarts from this frame, 0(first frame) by default
////    // Returns the texture co-ordinates to be used by OpenGl to render the sub texture.
////    constexpr std::array<gtl::Vec2f, 4> get_frame_uv(const Frame& frame) {
////        return {
////            // Top Right of Texture Bounds
////            gtl::Vec2f{(frame.size.x + frame.pos.x) / map_size_.x,(frame.pos.y + frame.size.y) / map_size_.y} 
////            // Bottom Right of Texture Bounds
////            ,gtl::Vec2f{(frame.size.x + frame.pos.x) / map_size_.x,frame.pos.y / map_size_.x} 
////            // Bottom Left of Texture Bounds
////            ,gtl::Vec2f{frame.pos.x / map_size_.x,frame.pos.y / map_size_.y} 
////            // Top Left of Texture Bounds
////            ,gtl::Vec2f{frame.pos.x / map_size_.x,(frame.pos.y + frame.size.y) / map_size_.y} }; 
////    }
////    constexpr std::array<float, 8> get_frame_uv_raw(const Frame& frame) {
////        return {
////            // Top Right of Texture Bounds
////            (frame.size.x + frame.pos.x) / map_size_.x,
////            (frame.pos.y + frame.size.y) / map_size_.y,
////            // Bottom Right of Texture Bounds
////            (frame.size.x + frame.pos.x) / map_size_.x,
////            frame.pos.y / map_size_.x,
////            // Bottom Left of Texture Bounds
////            frame.pos.x / map_size_.x,
////            frame.pos.y / map_size_.y,
////            // Top Left of Texture Bounds
////            frame.pos.x / map_size_.x,
////            (frame.pos.y + frame.size.y) / map_size_.y};
////    }
////public:
////    void addFrame(gtl::vec2<float> pos, gtl::vec2<float> size) { frames_.push_back({ pos,size }); }
////    void addAnimation(std::vector<size_t> frame_indices) { animations_.push_back({ frame_indices }); }
////    void setMapSize(gtl::Vec2f size) { map_size_ = size; };
////    void setActiveAnimation(size_t anim_idx, size_t init_frame) {
////        active_frame_ = init_frame;
////        active_animation_ = anim_idx;
////    };
////    void setActiveFrame(size_t active_frame) {
////        active_frame_ = active_frame;
////    };
////    std::array<gtl::Vec2f, 4> getActiveUV(){ return get_frame_uv(frames_.at(active_frame_)); }
////    std::array<float, 8>  getActiveUVRaw() { return get_frame_uv_raw(frames_.at(active_frame_)); };
////    constexpr gtl::vec2<float> getActiveAspect() {
////        return frames_.at(active_frame_).size.normalized(); // Get the unit vector of the sprite size
////    }
////    void NextFrame() {
////        if (active_frame_ >= animations_.at(active_animation_).size()) {
////            active_frame_ = init_frame_; // Reset back to init frame after last frame
////        }
////        else {
////            active_frame_++; // Active frame is the next one
////        }
////    };
////};