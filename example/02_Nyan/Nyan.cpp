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

#include <Lums/Lums.hpp>

class Nyan : public lm::GameState
{
public:
    Nyan()
    : _linear(true)
    {
        
    }

    void
    load()
    {
        _image.loadFile("Nyan.png");
        _proj = lm::ortho(0, 400, 400, 0);
        _prog.attach(lm::Shader("nyan.vert.glsl", lm::Shader::Vertex));
        _prog.attach(lm::Shader("nyan.frag.glsl", lm::Shader::Fragment));
        _prog.bindAttribLocation(lm::Vertex::Position, "pos");
        _prog.bindAttribLocation(lm::Vertex::Texture, "texcoord");
        _prog.bindAttribLocation(lm::Vertex::Color, "color");
        _prog.link();
        _prog.use();

        lm::uniform(_prog, "proj", _proj);
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
            if (event.key == lm::Key::V)
            {
                _linear = !_linear;
                _image.linear(_linear);
            }
            else
                lm::Core::instance().stop();
        }
    }

    void
    render()
    {
        _batch.begin();
        _batch.draw(_image, 0, {0.f, 0.f}, {2.f, 2.f});
        _batch.end();
    }

private:
    lm::Image           _image;
    lm::ShaderProgram   _prog;
    lm::SpriteBatch     _batch;
    lm::Matrix4f        _proj;
    bool                _linear;
};

int
main()
{
    lm::enableModule(lm::Module::All);
    lm::Core& core = lm::Core::instance();
    core.setWindow(new lm::Window(400, 400, "Nyan"));
    core.push<Nyan>();
    core.start();
}
