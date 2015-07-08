/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Anim.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums>

class Anim : public lm::GameState
{
public:
    void
    load()
    {
        auto& shader = lm::ShaderProvider::instance().get(0);

        _proj = lm::ortho(0, 800, 600, 0);
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
        auto& sk = lm::SkeletonProvider::instance().get(0);

        _batch.begin();
        _batch.draw(sk, tex, {300.f, 200.f, 0.f});
        _batch.end();
    }

private:
    lm::SpriteBatch     _batch;
    lm::Matrix4f        _proj;
};

int
main(int argc, char* argv[])
{
    if (argc != 4)
        return 1;

    lm::enableModule(lm::Module::All);

    lm::Core& core = lm::Core::instance();
    core.setWindow(new lm::Window(800, 600, "Anim"));

    auto& img = lm::ImageProvider::instance().set(0);
    img.setPath(argv[1], false);

    auto& tex = lm::TextureProvider::instance().set(0);
    tex.setImage(img);
    tex.pushAtlas(argv[2], false);

    auto& sk = lm::SkeletonProvider::instance().set(0);
    sk.load(argv[3], false);

    auto& shader = lm::ShaderProvider::instance().set(0);
    shader.attach(lm::Shader("anim.vert.glsl", lm::Shader::Vertex));
    shader.attach(lm::Shader("anim.frag.glsl", lm::Shader::Fragment));
    shader.bindAttribLocation(lm::Vertex::Position, "pos");
    shader.bindAttribLocation(lm::Vertex::Texture, "texcoord");
    shader.bindAttribLocation(lm::Vertex::Color, "color");
    shader.link();
    shader.use();

    core.push<Anim>();
    core.start();
}
