#ifndef FUNCTOR_H
#define FUNCTOR_H

template <typename R, typename... Args>
class FunctorImpl
{
public:
    virtual R operator()(Args...) = 0;
    virtual ~FunctorImpl() {}
};

template <typename Fun, typename R, typename... Args>
class FunctorHandler : public FunctorImpl<R, Args...>
{
public:
    explicit FunctorHandler(const Fun &fun) : fun_(fun) {}
    R operator()(Args... args)
    {
        return fun_(args...);
    }
private:
    Fun fun_;
};

template <typename Signature>
class Functor;

template <typename R, typename... Args>
class Functor<R (Args...)> {
private:
    typedef FunctorImpl<R, Args...> Impl;
    Impl *impl;
public:
    Functor();
    ~Functor() { if (impl) delete impl; }
    template <class Fun> Functor(const Fun fun)
        : impl(new FunctorHandler<Fun, R, Args...>(fun)) {}
    Functor(const Functor &);
    Functor& operator=(const Functor &);
    R operator()(Args... args) {
        return (*impl)(args...);
    }
};

#endif
