#pragma once


#include <vector>

namespace vux {

    template<typename T>
    struct Vec2 {
        T x;
        T y;
    };

    struct Transform {
        Vec2<float> scale;
        Vec2<float> rotate;
        Vec2<float> translate;
    };

    struct Vertux {
        Vec2<float> origin;
        Transform transform;

        Vertux* parent{ nullptr };
        std::vector<Vertux*> children;

        auto add_child(auto* vertux) {
            children.push_back(vertux);
            return vertux;
        }
    };

    class LayoutBASE {
    public:
        void set_target(Vertux* vtx) {
            target_vertux_ = vtx;
        }

        void apply(Vertux* vtx) {
            set_target(vtx);
            apply_impl(vtx);
        }

    private:
        Vertux* target_vertux_{ nullptr };
    protected:
        virtual void apply_impl(Vertux* vtx) = 0;
    public:
        LayoutBASE() = default;
        virtual ~LayoutBASE() = default;
    };

    class Layout : public LayoutBASE {
    public:
        enum class AnchorType { TOP, BOTTOM, RIGHT, LEFT, MIDDLE, FREE };
        Layout(Vec2<float> scale, AnchorType anchor) : LayoutBASE(), scale_(scale), anchor_(anchor) {
        }
        ~Layout() = default;
    private:
        Vec2<float> scale_{ 1.f,1.f };
        AnchorType anchor_{ AnchorType::FREE };
        void apply_impl(Vertux* vtx) override {
            // Parent size is zero when the vertux doesnt have one.
            Vec2<float> vtx_parent_size{ 0.f,0.f };
            if (vtx->parent != nullptr) {
                vtx_parent_size = vtx->parent->transform.scale;
            }

            auto& vtx_size = vtx->transform.scale;
            auto& vtx_origin = vtx->origin;

            // Set the scale of the vertux
            vtx_size.x *= scale_.x;
            vtx_size.y *= scale_.y;

            // Apply anchor positioning
            if (anchor_ == AnchorType::BOTTOM) {
                auto y_offset = -((vtx_parent_size.y / 2.f) - (vtx_size.y / 2.f));
                vtx_origin.y += y_offset;
            }
            else if (anchor_ == AnchorType::TOP) {
                auto y_offset = -( (vtx_parent_size.y / 2.f) - (vtx_size.y / 2.f));
                vtx_origin.y += y_offset;
            }

        }
    };


    static bool test(){
    // The main UI context
    Vertux main_canvas;
    main_canvas.transform.scale.x = 100;
    main_canvas.transform.scale.y = 100;

    // The top bar.
    Vertux top_bar;
    Layout top_bar_layout{{1.f,0.1f},Layout::AnchorType::TOP};

      return true;
    }
}