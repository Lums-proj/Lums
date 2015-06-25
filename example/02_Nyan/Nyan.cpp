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

static void
resizeApp(float scale)
{
    auto& window = lm::Core::instance().window();
    auto& tp = lm::TextureProvider::instance();
    auto& ip = lm::ImageProvider::instance();

    ip.set(0).setScale(scale);
    window.resize(400 * scale, 400 * scale);
    tp.reloadAll();
}

class Nyan : public lm::GameState
{
public:
    Nyan()
    : _scale(1.f)
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
        {
            if (event.key == lm::Key::Left)
            {
                _scale *= 0.9f;
                resizeApp(_scale);
            }
            else if (event.key == lm::Key::Right)
            {
                _scale *= 1.1f;
                if (_scale > 2.f)
                    _scale = 2.f;
                else
                    resizeApp(_scale);
            }
            else
                lm::Core::instance().stop();
        }
    }

    void
    render()
    {
        auto& tex = lm::TextureProvider::instance().get(0);

        _batch.begin();
        _batch.draw(tex, 0, {0.f, 0.f, 0.f}, {2.f, 2.f});
        _batch.end();
    }

private:
    lm::SpriteBatch     _batch;
    lm::Matrix4f        _proj;
    float               _scale;
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
    tex.pushAtlas(1, 1);
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
