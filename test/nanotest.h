// This is nanotest
// (c) Nax, 2014
// All distribution authorized.

// Version 1.1.1

#ifndef NANOTEST_H
#define NANOTEST_H

#include <cstdio>
#include <ctime>
#include <map>
#include <list>
#include <vector>
#include <iterator>

// Caps are evil, more evil than innocent macros

#define NANOTEST_STR_HELPER(str) (#str)
#define NANOTEST_VAR_HELPER(var) (_nanotest_var_ ## var ## _internal)
#define NANOTEST_FUN_HELPER(fun) (_nanotest_fun_ ## fun ## _internal)
#define describe(name) void NANOTEST_FUN_HELPER(name)(void);                   \
                       static _nanotest_test NANOTEST_VAR_HELPER(var)          \
                       = _nanotest_test(NANOTEST_STR_HELPER(name),             \
                       NANOTEST_FUN_HELPER(name));                             \
                       void NANOTEST_FUN_HELPER(name)(void)

#define NANOTEST_ASSERT(expr) do {                                             \
                                    _nanotest_get_map().active->asserts        \
                                    .push_back(_nanotest_assert());            \
                                    _nanotest_get_map().active->active->len += \
                                    _nanotest_get_map().active->follow ? 1 : 0;\
                                    if (_nanotest_get_map().active->follow     \
                                        && (expr))                             \
                                        _nanotest_get_map().active             \
                                        ->asserts[_nanotest_get_map().active   \
                                                ->assert_num].success = true;  \
                                    else if (_nanotest_get_map().active        \
                                             ->follow)                         \
                                      {_nanotest_get_map().active              \
                                                           ->follow=false;     \
                                        _nanotest_get_map().active             \
                                        ->asserts[_nanotest_get_map().active   \
                                                ->assert_num].trace =          \
                                                NANOTEST_STR_HELPER((expr));}  \
                                    _nanotest_get_map().active->assert_num++;  \
                              } while(false)



#define it(str) _nanotest_get_map().active->follow = true;                     \
                _nanotest_get_map().active->its.push_back(_nanotest_it(        \
                    _nanotest_get_map().active->assert_num, str));             \
                _nanotest_get_map().active->active =                           \
                    &(_nanotest_get_map().active->its.back());                 \
                if (true)

#define assert_if(expr)         NANOTEST_ASSERT(expr)
#define assert_unless(expr)     NANOTEST_ASSERT(!(expr))
#define assert_equal(a, b)      NANOTEST_ASSERT((a) == (b))
#define assert_not_equal(a, b)  NANOTEST_ASSERT((a) != (b))
#define assert_less(a, b)       NANOTEST_ASSERT((a) < (b))
#define assert_more(a, b)       NANOTEST_ASSERT((a) > (b))
#define assert_less_equal(a, b) NANOTEST_ASSERT((a) <= (b))
#define assert_more_equal(a, b) NANOTEST_ASSERT((a) >= (b))
#define assert_max_diff(a, b,c) NANOTEST_ASSERT((a) - (b) < (c) &&             \
                                                (a) - (b) > -(c))
#define assert_min_diff(a, b,c) NANOTEST_ASSERT((a) - (b) > (c) ||             \
                                                (a) - (b) < -(c))

#define assert_throw(expr, klass) do {                                         \
                                  try { (expr); }                              \
                                  catch (klass) { assert_if(true); break; }    \
                                  catch (...) { assert_if(false); break; }     \
                                  assert_if(false); } while (false)            \

#define assert_throw_any(expr)    do {                                         \
                                  try { (expr); }                              \
                                  catch (...) { assert_if(true); break; }      \
                                  assert_if(false); } while (false)            \

#define assert_no_throw(expr, klass) do {                                      \
                                  try { (expr); }                              \
                                  catch (klass) { assert_if(false); break; }   \
                                  catch (...) { assert_if(true); break; }      \
                                  assert_if(false); } while (true)             \

#define assert_no_throw_any(expr) do {                                         \
                                  try { (expr); }                              \
                                  catch (...) { assert_if(false); break; }     \
                                  assert_if(false); } while (true)             \

#define assert_throw_fun(fun, klass)        assert_throw((fun)();, klass)
#define assert_throw_any_fun(fun, klass)    assert_throw_any((fun)();, klass)
#define assert_no_throw_fun(fun, klass)     assert_no_throw((fun)();, klass)
#define assert_no_throw_any_fun(fun, klass) assert_no_throw_any((fun)();, klass)

struct _nanotest_test;
typedef void (*_nanotest_fun)(void);
typedef std::map<const char *, _nanotest_test*> _nanotest_map_internal;

struct _nanotest_misc
{
    _nanotest_misc() : color(false) {}
    double        total_time;
    bool          color;
};

struct _nanotest_map
{
    _nanotest_map_internal  map;
    _nanotest_test*         active;
    _nanotest_misc          misc;
};

// An helper function for the dummy class (see below)
inline _nanotest_map& _nanotest_get_map(void)
{
    static _nanotest_map m;

    return m;
}

struct _nanotest_it
{
    _nanotest_it(int _from, const char* _msg)
    {
        from = _from;
        msg = _msg;
        len = 0;
    }
    int                 from;
    int                 len;
    const char*         msg;
};

struct _nanotest_assert
{
    _nanotest_assert()
    {
        ran = false;
        success = false;
    }
    bool                ran;
    bool                success;
    const char*         trace;
};

// A dummy class, abusing ctor side effect on a static variable
// to create some kind of 'inline singleton variable', keeping
// this lib header-only.
// (Never do that in production. Please.)
struct _nanotest_test
{
    _nanotest_test(const char *str, _nanotest_fun f)
    {
        name = str;
        fun = f;
        _nanotest_get_map().map[str] = this;
        assert_num = 0;
        follow = true;
    }
    const char*                     name;
    _nanotest_fun                   fun;
    int                             assert_num;
    std::vector<_nanotest_assert>   asserts;
    std::list<_nanotest_it>         its;
    _nanotest_it*                   active;
    bool                            follow;
};

inline void _nanotest_run(const char* name)
{
    _nanotest_test* test = _nanotest_get_map().map[name];

    _nanotest_get_map().active = test;
    test->fun();
}

inline void _nanotest_run_all(void)
{
    clock_t start, end;

    start = clock();
    for (_nanotest_map_internal::iterator it = _nanotest_get_map().map.begin();
         it != _nanotest_get_map().map.end(); ++it)
        _nanotest_run(it->first);
    end = clock();
    _nanotest_get_map().misc.total_time = static_cast<double>(end - start)
                                          / CLOCKS_PER_SEC;
}

// Using \r\n instead of \n to be compatible with Windows.
// (Even if windows dev don't test their softwares...)
inline int _nanotest_display(void)
{
    const char*     trace;
    int             total = 0;
    int             fails = 0;
    _nanotest_map_internal& m = _nanotest_get_map().map;
    _nanotest_misc& data = _nanotest_get_map().misc;
    bool c = data.color;

    std::printf("Ran %zu test suite(s) in %s%lf%s second(s)\r\n",
                m.size(),
                c ? "\e[33m" : "",
                data.total_time,
                c ? "\e[0m" : "");
    for (_nanotest_map_internal::iterator it = m.begin(); it != m.end(); ++it)
    {
        std::printf("\r\n%s%s%s\r\n", c ? "\e[1m" : "", it->first,
                    c ? "\e[0m" : "");
        for (std::list<_nanotest_it>::iterator it2 = it->second->its.begin();
             it2 != it->second->its.end(); ++it2)
        {
            std::printf("    it %-60s %s", it2->msg, c ? "\e[1m" : "");
            trace = NULL;
            int i;
            for (i = 0; i < it2->len; i++)
            {
                if (!it->second->asserts[it2->from + i].success)
                {
                    trace = it->second->asserts[it2->from + i].trace;
                    break;
                }
            }
            total++;
            if (trace)
            {
                fails++;
                std::printf("[%sFAIL%s]%s\r\n", c ? "\e[31m" : "",
                                                c ? "\e[37m" : "",
                                                c ? "\e[30m" : "");
                std::printf("      -> at assert %d\r\n", i + 1);
                std::printf("      -> trace %s%s\r\n", trace, c ? "\e[0m" : "");
            }
            else
                std::printf("[%s OK %s]%s\r\n", c ? "\e[32m" : "",
                                                c ? "\e[37m" : "",
                                                c ? "\e[0m" : "");
        }
    }
    std::printf("\r\n%sFinished: %s%d Test(s)%s, %s%d Success%s, "
                "%s%d Failure(s)%s.%s\r\n",
                c ? "\e[1m" : "",
                c ? "\e[33m" : "", total,
                c ? "\e[0;1m" : "",
                c ? "\e[32m" : "", total - fails,
                c ? "\e[0;1m" : "",
                c ? "\e[31m" : "", fails,
                c ? "\e[0;1m" : "",
                c ? "\e[0m" : "");
    return (fails == 0 ? 0 : 1);
}

inline int nanotest_main(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (!std::strcmp(argv[i], "-c"))
            _nanotest_get_map().misc.color = true;
    }
    _nanotest_run_all();
    return _nanotest_display();
}

#ifdef AUTO_MAIN
int main(int argc, char* argv[])
{
    return nanotest_main(argc, argv);
}
#endif

#endif
