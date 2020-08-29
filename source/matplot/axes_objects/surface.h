//
// Created by Alan Freitas on 2020-07-04.
//

#ifndef MATPLOTPLUSPLUS_SURFACE_H
#define MATPLOTPLUSPLUS_SURFACE_H

#include <array>
#include <optional>

#include <matplot/util/concepts.h>
#include <matplot/util/handle_types.h>
#include <matplot/core/figure.h>

#include <matplot/core/axes_object.h>
#include <matplot/core/line_spec.h>
#include <matplot/util/common.h>

namespace matplot {
    class axes;

    /// Surfaces might include data for contours but, if you only want contours,
    /// it's best to use the contour, contourf, fcontour functions to plot it in 2d
    class surface : public axes_object {
    public:
        explicit surface(class axes* parent);

        /// Grid surface
        surface(class axes* parent, const vector_2d& X, const vector_2d& Y, const vector_2d& Z, const vector_2d& C, const std::string& line_spec = "");

        /// Parametric surface
//        surface(class xlim* parent, const vector_1d& x, const vector_1d& y, const vector_1d& z, const vector_1d& c, const std::string& line_spec = "");

        /// If we receive an axes_handle, we can convert it to a raw
        /// pointer because there is no ownership involved here
        template <class ...Args>
        surface(const axes_handle& parent, Args... args)
            : surface(parent.get(), args...) {}

    public /* mandatory virtual functions */:
        std::string set_variables_string() override;
        std::string plot_string() override;
        std::string legend_string(const std::string& title) override;
        std::string data_string() override;
        double xmax() override;
        double xmin() override;
        double ymax() override;
        double ymin() override;
        enum axes_object::axes_category axes_category() override;

    public /* getters and setters */:
        surface& line_style(const std::string& line_spec);

        const line_spec &line_spec() const;
        class line_spec &line_spec();
        surface& line_spec(const class line_spec &line_spec);

        const vector_2d &Y_data() const;
        surface& Y_data(const vector_2d &Y_data);

        const vector_2d &X_data() const;
        surface& X_data(const vector_2d &X_data);

        const vector_2d &Z_data() const;
        surface& Z_data(const vector_2d &Z_data);

        size_t norm() const;
        surface& norm(size_t norm);

        const vector_2d &x_data() const;
        surface& x_data(const vector_2d &x_data);

        const vector_2d &y_data() const;
        surface& y_data(const vector_2d &y_data);

        const vector_2d &z_data() const;
        surface& z_data(const vector_2d &z_data);

        bool hidden_3d() const;
        surface& hidden_3d(bool hidden_3_d);

        bool surface_visible() const;
        surface& surface_visible(bool surface_visible);

        bool surface_in_2d() const;
        surface& surface_in_2d(bool surface_in_2d);

        bool palette_map_at_bottom() const;
        surface& palette_map_at_bottom(bool palette_map_at_bottom);

        bool palette_map_at_surface() const;
        surface& palette_map_at_surface(bool palette_map_at_surface);

        bool palette_map_at_top() const;
        surface& palette_map_at_top(bool palette_map_at_top);

        bool contour_base() const;
        surface& contour_base(bool contour_base);

        bool contour_surface() const;
        surface& contour_surface(bool contour_surface);

        size_t contour_levels() const;
        surface& contour_levels(size_t contour_levels);

        const std::vector<double> &contour_values() const;
        surface& contour_values(const std::vector<double> &contour_values);

        bool contour_text() const;
        surface& contour_text(bool contour_text);

        const float font_size() const;
        surface& font_size(const float &font_size);

        const std::string font() const;
        surface& font(const std::string &font);

        const std::string &font_weight() const;
        surface& font_weight(const std::string &font_weight);

        const color_array &font_color() const;
        surface& font_color(const color_array &font_color);
        surface& font_color(const std::string &font_color);

        bool depthorder() const;

        surface& depthorder(bool depthorder);

        float face_alpha() const;
        surface& face_alpha(float face_alpha);

        bool lighting() const;
        surface& lighting(bool lighting);

        float primary() const;
        surface& primary(float amount);

        float specular() const;
        surface& specular(float amount);

        const class line_spec &contour_line_spec() const;
        class line_spec &contour_line_spec();
        surface& contour_line_spec(const class line_spec &contour_line_spec);

        bool curtain() const;
        surface& curtain(bool curtain);

        bool waterfall() const;
        surface& waterfall(bool waterfall);

        bool fences() const;
        surface& fences(bool fences);

        bool ribbons() const;
        surface& ribbons(bool ribbons);

        double ribbon_width() const;
        surface& ribbon_width(double ribbon_width);

        bool visible() const;
        surface& visible(bool visible);

    public /* getters and setters bypassing the line_spec */:
        float line_width() const;
        surface& line_width(float line_width);

        const std::array<float, 4>& edge_color() const;

        template <class T>
        surface& edge_color(T c) {
            line_spec().color(c);
            touch();
            return *this;
        }

        inline surface& edge_color(std::initializer_list<float> c) {
            line_spec().color(c);
            touch();
            return *this;
        }

        double zmin() override;
        double zmax() override;

    protected:
        void maybe_update_line_spec();
        std::string grid_data_string();
        std::string ribbon_data_string();
        size_t create_line_index();

    protected:
        /// Data in the xlim
        vector_2d X_data_{};
        vector_2d Y_data_{};
        vector_2d Z_data_{};
        vector_2d C_data_{};

        /// Interpret data as a flat array of parametrics values
        /// If false, data needs to represent a grid
        /// If true, data represents a free form
        bool is_parametric_{false};

        /// Preprocess zmin / zmax
        double zmin_{NaN};
        double zmax_{NaN};

        /// Style
        size_t norm_{2};
        bool hidden3d_{false};
        bool depthorder_{false};
        float face_alpha_{.95};
        class line_spec line_spec_;
        bool lighting_{false};
        float primary_{-1.};
        float specular_{-1.};
        bool curtain_{false};
        bool waterfall_{false};
        bool fences_{false};
        bool ribbons_{false};
        double ribbon_width_{0.75};

        // Line surface
        bool surface_visible_{true};
        bool surface_in_2d_{false};

        // Solid surface
        bool palette_map_at_bottom_{false};
        bool palette_map_at_surface_{true};
        bool palette_map_at_top_{false};

        class line_spec contour_line_spec_;
        bool contour_base_{false};
        bool contour_surface_{false};
        size_t contour_levels_{9};
        std::vector<double> contour_values_{};

        bool contour_text_{false};
        std::optional<float> font_size_{std::nullopt};
        std::optional<std::string> font_{std::nullopt};
        std::string font_weight_{"normal"};
        color_array font_color_{0,0,0,0};

        /// True if visible
        bool visible_{true};
    };
}

#endif //MATPLOTPLUSPLUS_SURFACE_H
