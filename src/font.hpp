#ifndef LD40_FONT_HPP
#define LD40_FONT_HPP

#include <sushi/mesh.hpp>
#include <sushi/shader.hpp>
#include <sushi/texture.hpp>

#include <msdfgen.h>
#include <msdfgen-ext.h>

#include <string>
#include <unordered_map>
#include <memory>

struct FontDeleter {
    void operator()(msdfgen::FontHandle* ptr) {
        msdfgen::destroyFont(ptr);
    }
};

class msdf_font {
public:
    struct glyph {
        sushi::static_mesh mesh;
        sushi::texture_2d texture;
        float advance;
    };

    msdf_font() = default;
    msdf_font(const std::string& filename);

    void bind_shader() const;
    const glyph& get_glyph(int unicode);

private:
    std::unique_ptr<msdfgen::FontHandle, FontDeleter> font;
    std::unordered_map<int, glyph> glyphs;
    sushi::unique_program program;
};

#endif //LD40_FONT_HPP

