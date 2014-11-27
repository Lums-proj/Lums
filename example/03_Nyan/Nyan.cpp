#include <Lums/Lums.h>

class Nyan : public lm::GameState
{
public:
    Nyan(lm::Core* core)
    : lm::GameState(core)
    {
        _image.LoadFile("Nyan.png");
    }

    void
    Update()
    {

    }

    void
    HandleEvent(const lm::Event& event)
    {
        if (event.type == SDL_KEYDOWN)
            Core().Stop();
    }

    void
    Render()
    {
        glEnable(GL_TEXTURE_2D);
        _image.Bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(-1, -1);
        glTexCoord2f(1, 0);
        glVertex2f(1, -1);
        glTexCoord2f(1, 1);
        glVertex2f(1, 1);
        glTexCoord2f(0, 1);
        glVertex2f(-1, 1);
        glEnd();
        glDisable(GL_TEXTURE_2D);

    }

private:
    lm::Image   _image;
};

int
main()
{
    lm::Core core(400, 400, "Nyan");

    core.Push<Nyan>();
    core.Start();
}