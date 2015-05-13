/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Cube.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <Lums/Lums.hpp>

class Cube : public lm::GameState
{
public:
    Cube();
    void    load();
    void    update();
    void    handleEvent(const lm::Event& event);
    void    render();
    void    unload();
    
private:
    lm::Vector2a            _angle;
    lm::Vector2f            _speed;
    lm::Projection          _proj;
    lm::VertexBufferP3C4    _vbo;
    lm::ShaderProgram       _shader;
};

using namespace lm;

#define ARR_SIZE(arr)   (sizeof(arr) / sizeof(*arr))

const static GLfloat
vertices[] = {
     1,  1,  1,
     1,  1, -1,
     1, -1,  1,
    -1,  1,  1,
     1, -1, -1,
    -1,  1, -1,
    -1, -1,  1,
    -1, -1, -1
};

const static GLfloat
colors[] = {
    1, 0, 0,
    0, 1, 0,
    0, 0, 1,
    1, 1, 0,
    1, 0, 1,
    0, 1, 1,
    1, 0, 1,
    1, 1, 1
};

const static GLubyte
indices[] = {
    0, 2, 6, 3,
    3, 5, 7, 6,
    5, 1, 4, 7,
    1, 0, 2, 4,
    1, 0, 3, 5,
    2, 4, 7, 6
};

Cube::Cube()
: _speed(10, 0)
{

}

static void
idx_push(lm::VertexBufferP3C4& vbo, GLubyte idx)
{
    const GLfloat* vptr = vertices + 3 * idx;
    const GLfloat* cptr = colors + 3 * idx;

    vbo.push(vptr[0], vptr[1], vptr[2], cptr[0], cptr[1], cptr[2], 1.f);
}

static void
vbo_push(lm::VertexBufferP3C4& vbo, GLubyte i1, GLubyte i2, GLubyte i3)
{
    idx_push(vbo, i1);
    idx_push(vbo, i2);
    idx_push(vbo, i3);
}

void
Cube::load()
{
    //glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
   // glEnable(GL_CULL_FACE);
    for (int i = 0; i < ARR_SIZE(indices); i += 4)
    {
        const GLubyte* ptr = indices + i;

        vbo_push(_vbo, ptr[0], ptr[1], ptr[2]);
        vbo_push(_vbo, ptr[0], ptr[2], ptr[3]);
    }
    _vbo.send();
    _shader.attach(lm::Shader("cube.frag.glsl", lm::Shader::Fragment));
    _shader.attach(lm::Shader("cube.vert.glsl", lm::Shader::Vertex));
    _shader.bindAttribLocation(lm::Vertex::Position, "pos");
    _shader.bindAttribLocation(lm::Vertex::Color, "color");
    _shader.link();
    _shader.use();
    _proj.projection = lm::perspective(70.f, 800.f / 600.f, 0.01f, 1000.f);
}

void
Cube::update()
{
    _angle.x += Angle::degrees(0.1) * _speed.x;
    _angle.y += Angle::degrees(0.1) * _speed.y;
}

void
Cube::handleEvent(const Event& event)
{
    if (event.type == Event::Type::KeyDown)
    {
        switch (event.key)
        {
            case Key::Escape:
                Core::get().stop();
                break;
            case Key::Right:
                _speed.x++;
                break;
            case Key::Left:
                _speed.x--;
                break;
            case Key::Up:
                _speed.y++;
                break;
            case Key::Down:
                _speed.y--;
                break;
            default:
                break;
        }
    }
}

void
Cube::render()
{
    _proj.view = lm::lookAt({2.f, 2.f, 2.f}, {0, 0, 0}, {0, 1.f, 0});
    _proj.model = Matrix4f::identity();
    rotate(_proj.model, _angle.x.toDegrees(), {0, 1, 0});
    rotate(_proj.model, _angle.y.toDegrees(), {0, 0, 1});
    lm::uniform(_shader, "model", _proj.model);
    lm::uniform(_shader, "view", _proj.view);
    lm::uniform(_shader, "projection", _proj.projection);
    _vbo.draw(GL_TRIANGLES);
}

void
Cube::unload()
{
    glDisable(GL_DEPTH_TEST);
    _vbo.reset();
}

/* main */

int
main()
{
    lm::Core gl(800, 600, "Cube");

    gl.push<Cube>();
    gl.start();
}
