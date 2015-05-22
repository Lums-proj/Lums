/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    CubePolaroid.cpp                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <Lums>

class CubePolaroid : public lm::GameState
{
public:
    CubePolaroid();
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
    lm::ShaderPipeline      _pipeline;
    bool                    _dirty;
    bool                    _negFx;
    bool                    _blurFx;
};

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

CubePolaroid::CubePolaroid()
: _speed(10, 0)
, _dirty(false)
, _negFx(false)
, _blurFx(false)
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
CubePolaroid::load()
{
    glEnable(GL_DEPTH_TEST);
    for (int i = 0; i < ARR_SIZE(indices); i += 4)
    {
        const GLubyte* ptr = indices + i;

        vbo_push(_vbo, ptr[0], ptr[1], ptr[2]);
        vbo_push(_vbo, ptr[0], ptr[2], ptr[3]);
    }
    _vbo.send();
    _proj.projection = lm::perspective(70.f, 800.f / 600.f, 0.01f, 1000.f);
    _pipeline.setWindow(lm::Core::instance().window());
}

void
CubePolaroid::update()
{
    _angle.x += lm::Angle::degrees(0.1) * _speed.x;
    _angle.y += lm::Angle::degrees(0.1) * _speed.y;

    if (_dirty)
    {
        _dirty = false;
        _pipeline.clear();
        if (_negFx)
            _pipeline.append(lm::ShaderProvider::instance().get(1));
        if (_blurFx)
            _pipeline.append(lm::ShaderProvider::instance().get(2));
    }
}

void
CubePolaroid::handleEvent(const lm::Event& event)
{
    if (event.type == lm::Event::Type::KeyDown)
    {
        switch (event.key)
        {
            case lm::Key::Escape:
                lm::Core::instance().stop();
                break;
            case lm::Key::Right:
                _speed.x++;
                break;
            case lm::Key::Left:
                _speed.x--;
                break;
            case lm::Key::Up:
                _speed.y++;
                break;
            case lm::Key::Down:
                _speed.y--;
                break;
            case lm::Key::N:
                _negFx = !_negFx;
                _dirty = true;
                break;
            case lm::Key::B:
                _blurFx = !_blurFx;
                _dirty = true;
                break;
            default:
                break;
        }
    }
}

void
CubePolaroid::render()
{
    auto& shader = lm::ShaderProvider::instance().get(0);

    _pipeline.bind();
    shader.use();
    _proj.view = lm::lookAt({2.f, 2.f, 2.f}, {0, 0, 0}, {0, 1.f, 0});
    _proj.model = lm::Matrix4f::identity();
    lm::rotate(_proj.model, _angle.x.toDegrees(), {0, 1, 0});
    lm::rotate(_proj.model, _angle.y.toDegrees(), {0, 0, 1});
    lm::uniform(shader, "model", _proj.model);
    lm::uniform(shader, "view", _proj.view);
    lm::uniform(shader, "projection", _proj.projection);
    _vbo.draw(GL_TRIANGLES);
    _pipeline.render();
}

void
CubePolaroid::unload()
{
    glDisable(GL_DEPTH_TEST);
    _vbo.reset();
}

/* main */

int
main()
{
    lm::enableModule(lm::Module::All);
    lm::Core& gl = lm::Core::instance();
    gl.setWindow(new lm::Window(800, 600, "Cube Polaroid"));

    auto& sp = lm::ShaderProvider::instance().set(0);
    auto& fx = lm::ShaderProvider::instance().set(1);
    auto& s = lm::ShaderProvider::instance();

    fx.attach(lm::Shader("gfx_neg.frag.glsl", lm::Shader::Fragment));
    fx.attach(lm::Shader("gfx.vert.glsl", lm::Shader::Vertex));
    fx.bindAttribLocation(lm::Vertex::Position, "vPos");
    fx.bindAttribLocation(lm::Vertex::Texture, "tPos");
    fx.link();

    sp.attach(lm::Shader("cube_polaroid.frag.glsl", lm::Shader::Fragment));
    sp.attach(lm::Shader("cube_polaroid.vert.glsl", lm::Shader::Vertex));
    sp.bindAttribLocation(lm::Vertex::Position, "pos");
    sp.bindAttribLocation(lm::Vertex::Color, "color");
    sp.link();

    {
        auto& shader = s.set(2);

        shader.attach(lm::Shader("gfx_blur_x.frag.glsl", lm::Shader::Fragment));
        shader.attach(lm::Shader("gfx.vert.glsl", lm::Shader::Vertex));
        shader.bindAttribLocation(lm::Vertex::Position, "vPos");
        shader.bindAttribLocation(lm::Vertex::Texture, "tPos");
        shader.link();
    }

    gl.push<CubePolaroid>();
    gl.start();
}
