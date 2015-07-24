/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Font.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums>

class Font : public lm::GameState
{
public:
    Font()
    {
        
    }

    void
    load()
    {
        auto& shader = lm::ShaderProvider::instance().get(0);
        _proj = lm::ortho(0, 400, 0, 400);
        lm::uniform(shader, "proj", _proj);
    }

    void
    update()
    {

    }

    void
    handleEvent(const lm::Event& event)
    {
        if (event.type == lm::Event::Type::KeyDown)
            lm::Core::instance().stop();
    }

    void
    render()
    {
        _sb.begin();
        _sb.draw(lm::FontProvider::instance().get(0), "Salut Voisin AVA!");
        _sb.end();
    }

private:
    lm::SpriteBatch       _sb;
    lm::Matrix4f          _proj;
};

int
main()
{
    lm::enableModule(lm::Module::All);

    lm::Core& core = lm::Core::instance();
    core.setWindow(new lm::Window(400, 400, "Font"));

    auto& shader = lm::ShaderProvider::instance().set(0);
    shader.attach(lm::Shader("font.vert.glsl", lm::Shader::Vertex));
    shader.attach(lm::Shader("font.frag.glsl", lm::Shader::Fragment));
    shader.bindAttribLocation(lm::Vertex::Position, "pos");
    shader.bindAttribLocation(lm::Vertex::Texture, "texcoord");
    shader.bindAttribLocation(lm::Vertex::Color, "color");
    shader.link();
    shader.use();

    auto& font = lm::FontProvider::instance().set(0);
    font.setPath("/Library/Fonts/AppleGothic.ttf", false);
    font.setSize(50.f);

    GLint max;
    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &max);
    std::cout << max << std::endl;

    core.push<Font>();
    core.start();
}
