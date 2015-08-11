/*     __    __                                                              */
/*     \ \  / /         xtest 1.0.0                                          */
/*      \ \/ /                                                               */
/*      / /\ \                                                               */
/*     /_/  \_\                                                              */
/*                                                                           */

#ifndef XTEST_HPP_
#define XTEST_HPP_

#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <vector>

#define XUNUSED(x)          (void)x
#define XMAIN               int main(int argc, char* argv[]) {                  \
                                XUNUSED(argc);                                  \
                                XUNUSED(argv);                                  \
                                return XTestSuite::instance().run();            \
                            }
#define XNAME2_(cnt, id)    _xtest_ ## cnt ## id ## _
#define XNAME_(cnt, id)     XNAME2_(cnt, id)
#define XTEST(name)         static void XNAME_(__LINE__, func) (int);           \
                            static XTest XNAME_(__LINE__, test)                 \
                            (name, XNAME_(__LINE__, func), __FILE__, __LINE__); \
                            static void XNAME_(__LINE__, func) (int _xpipe_)

#define XASSERT(cond, msg)  if (!(cond)) {                                      \
                                dprintf(_xpipe_, "at '%s' <%s:%d>\n",           \
                                    msg, __FILE__, __LINE__);                   \
                                dprintf(_xpipe_, " * %s\n", #cond);             \
                                close(_xpipe_);                                 \
                                exit(1);                                        \
                            }

#define XASSERT_EQ(a, b, msg)    XASSERT(a == b, msg)
#define XASSERT_NEQ(a, b, msg)   XASSERT(a != b, msg)
#define XASSERT_LT(a, b, msg)    XASSERT(a < b, msg)
#define XASSERT_LTE(a, b, msg)   XASSERT(a <= b, msg)
#define XASSERT_GT(a, b, msg)    XASSERT(a > b, msg)
#define XASSERT_GTE(a, b, msg)   XASSERT(a >= b, msg)
#define XASSERT_Z(a, msg)        XASSERT(a == 0, msg)
#define XASSERT_NZ(a, b, msg)    XASSERT(a != 0, msg)

class XTest {
public:
    using function = void (*)(int);
    
    XTest(const std::string& name, function func, const std::string& file, int line)
    : name_(name), func_(func), file_(file), line_(line) {
        registerSelf();
    }

    void    run() {
        pid_t pid;
        int p[2];
        char buffer[8192];

        pipe(p);
        pid = fork();

        if (!pid) {
            close(p[0]);
            func_(p[1]);
            close(p[1]);
            exit(0);
        }
        close(p[1]);
        int returnCode;
        waitpid(pid, &returnCode, 0);
        if (WIFEXITED(returnCode) && WEXITSTATUS(returnCode) == 0) {
            success_ = true;
            putchar('.');
        } else {
            success_ = false;
            fputs("\e[31;1mE\e[0m", stdout);
            int len = read(p[0], buffer, 8191);
            buffer[len] = 0;
            errorMsg_ = buffer;
        }
        close(p[0]);
        fflush(stdout);
    }

    const std::string&  name() const { return name_; }
    const std::string&  file() const { return file_; }
    int                 line() const { return line_; }
    bool                success() const { return success_; }
    const std::string&  errorMsg() const { return errorMsg_; }
    void                registerSelf();

private:
    std::string     name_;
    function        func_;
    std::string     file_;
    int             line_;
    bool            success_;
    std::string     errorMsg_;
};

class XTestSuite {
public:
    XTestSuite(const XTestSuite&) = delete;
    XTestSuite& operator=(const XTestSuite&) = delete;

    int run() {
        int errors = 0;

        for (auto t : tests_)
            t->run();
        fputs("\n\n", stdout);
        for (auto t : tests_) {
            if (!t->success()) {
                errors++;
                printf("In test '%s' <%s:%d>\n", t->name().c_str(), t->file().c_str(), t->line());
                fputs(t->errorMsg().c_str(), stdout);
                putchar('\n');
            }
        }
        printf("Ran %zu test%s, %d error%s\n", tests_.size(), (tests_.size() > 1 ? "s" : ""), errors, (errors > 1 ? "s" : ""));
        return errors ? 1 : 0;
    }

    void registerTest(XTest& test) {
        tests_.push_back(&test);
    }

    static XTestSuite& instance() {
        static XTestSuite suite;
        return suite;
    }


private:
    XTestSuite() {};

    std::vector<XTest*> tests_;
};

inline void XTest::registerSelf() {
    XTestSuite::instance().registerTest(*this);
}

#endif
