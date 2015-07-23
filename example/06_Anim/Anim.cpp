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
    sk(const lm::Skeleton& skeleton)
    {
        _batch.reset();
        _bones.reset();
        for (unsigned i = 1; i < skeleton.bones().size(); ++i)
        {
            lm::Matrix4f parentMat = lm::Matrix4f::identity();
            lm::Matrix4f childMat = parentMat;

            skeleton.transformBone(childMat, i);
            skeleton.transformBone(parentMat, skeleton.bones()[i].parent());

            lm::Vector4f p0 = { 0, 0, 0, 1 };
            lm::Vector4f p1 = p0;

            p0 = parentMat * p0;
            p1 = childMat * p1;

            _batch.push(p0.x, p0.y, 0, 0, 1, 0, 1);
            _batch.push(p1.x, p1.y, 0, 1, 0, 0, 1);
            _bones.push(p0.x, p0.y, 0, 1, 0, 1, 1);
            _bones.push(p1.x, p1.y, 0, 1, 0, 1, 1);

        }
        _batch.send();
        _bones.send();
    }

    void
    load()
    {
        auto& shader = lm::ShaderProvider::instance().get(0);
        auto& shader1 = lm::ShaderProvider::instance().get(1);

        _sk = lm::SkeletonProvider::instance().get(0).create();
        _sk.setAnimation("Walk");

        shader.use();

        _proj = lm::ortho(0, 800, 0, 600, -100, 100);
        lm::uniform(shader, "proj", _proj);
        
        shader1.use();
        lm::uniform(shader1, "proj", _proj);
        _view = lm::Matrix4f::identity();
        lm::translate(_view, { 400, 0, 0 });

        shader.use();
        lm::uniform(shader, "view", _view);
        
        shader1.use();
        lm::uniform(shader1, "view", _view);

        sk(_sk);
    }

    void
    update()
    {
        static int i = -1;

        ++i;
        if (i > 180)
        {
            _sk.setAnimation("Walk");
            i = 0;
        }
        _sk.update();
        //this->sk(_sk);
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
        auto& sp = lm::ShaderProvider::instance();

        sp.get(1).use();
        _sb.begin();
        _sb.draw(_sk, lm::TextureProvider::instance().get(0));
        _sb.end();

        sp.get(0).use();

        glPointSize(5);
        //_batch.draw(GL_LINES);
        //_bones.draw(GL_POINTS);
    }

private:
    lm::SpriteBatch             _sb;
    lm::Skeleton                _sk;
    lm::VertexBufferP3C4        _batch;
    lm::VertexBufferP3C4        _bones;
    lm::Matrix4f                _proj;
    lm::Matrix4f                _view;
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
    shader.bindAttribLocation(lm::Vertex::Color, "color");
    shader.link();
    
    auto& shader1 = lm::ShaderProvider::instance().set(1);
    shader1.attach(lm::Shader("animtex.vert.glsl", lm::Shader::Vertex));
    shader1.attach(lm::Shader("animtex.frag.glsl", lm::Shader::Fragment));
    shader1.bindAttribLocation(lm::Vertex::Position, "pos");
    shader1.bindAttribLocation(lm::Vertex::Texture, "tex");
    shader1.bindAttribLocation(lm::Vertex::Color, "color");
    shader1.link();


    glDisable(GL_DEPTH_TEST);

    core.push<Anim>();
    core.start();
}
