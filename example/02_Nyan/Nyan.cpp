/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Nyan.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums>

class Nyan : public lm::GameState
{
public:
    Nyan()
    {
        
    }

    void
    load()
    {
        auto& shader = lm::ShaderProvider::instance().get(0);

        _proj = lm::ortho(0, 400, 400, 0);
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
        auto& tex = lm::TextureProvider::instance().get(0);

        _batch.begin();
        _batch.draw(tex, 0, {0.f, 0.f}, {2.f, 2.f});
        _batch.end();
    }

private:
    lm::SpriteBatch     _batch;
    lm::Matrix4f        _proj;
};

int
main()
{
    lm::enableModule(lm::Module::All);

    lm::Core& core = lm::Core::instance();
    core.setWindow(new lm::Window(400, 400, "Nyan"));

    auto& img = lm::ImageProvider::instance().set(0);
    img.setPath("Nyan.png");

    auto& tex = lm::TextureProvider::instance().set(0);
    tex.setImage(img);

    auto& shader = lm::ShaderProvider::instance().set(0);
    shader.attach(lm::Shader("nyan.vert.glsl", lm::Shader::Vertex));
    shader.attach(lm::Shader("nyan.frag.glsl", lm::Shader::Fragment));
    shader.bindAttribLocation(lm::Vertex::Position, "pos");
    shader.bindAttribLocation(lm::Vertex::Texture, "texcoord");
    shader.bindAttribLocation(lm::Vertex::Color, "color");
    shader.link();
    shader.use();

    core.push<Nyan>();
    core.start();
}
