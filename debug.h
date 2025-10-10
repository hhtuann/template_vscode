inline string to_string(const string &s)
{
    return '"' + s + '"';
}

inline string to_string(char c)
{
    return "'" + string(1, c) + "'";
}

inline string to_string(const char *s)
{
    return to_string(string(s));
}

inline string to_string(bool b)
{
    return b ? "true" : "false";
}

template <typename A, typename B>
inline string to_string(const pair<A, B> &p)
{
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename... T>
inline string to_string(const tuple<T...> &t)
{
    return apply([](const auto &...elems)
                 {
        string res = "(";
        ((res += to_string(elems) + ", "), ...);
        if constexpr (sizeof...(T) > 0) res.pop_back(), res.pop_back();
        return res + ")"; }, t);
}

template <size_t N>
inline string to_string(const bitset<N> &b)
{
    return b.to_string();
}

template <typename T>
inline string to_string(const T &container)
{
    string res = "{";
    bool first = true;
    for (const auto &x : container)
    {
        if (!first)
            res += ", ";
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template <typename T, typename C = deque<T>>
inline string to_string(stack<T, C> st)
{
    string res = "{";
    bool first = true;
    while (!st.empty())
    {
        if (!first)
            res += ", ";
        first = false;
        res += to_string(st.top());
        st.pop();
    }
    res += "}";
    return res;
}

template <typename T, typename C = deque<T>>
inline string to_string(queue<T, C> q)
{
    string res = "{";
    bool first = true;
    while (!q.empty())
    {
        if (!first)
            res += ", ";
        first = false;
        res += to_string(q.front());
        q.pop();
    }
    res += "}";
    return res;
}

template <typename T, typename C = vector<T>, typename Comp = less<T>>
inline string to_string(priority_queue<T, C, Comp> pq)
{
    string res = "{";
    bool first = true;
    while (!pq.empty())
    {
        if (!first)
            res += ", ";
        first = false;
        res += to_string(pq.top());
        pq.pop();
    }
    res += "}";
    return res;
}

inline void eprintln(const char *fmt, ...)
{
    va_list args, args2;
    va_start(args, fmt);
    va_copy(args2, args);

    int n = vsnprintf(nullptr, 0, fmt, args);
    va_end(args);

    if (n < 0)
    {
        va_end(args2);
        return;
    }

    string buf;
    buf.resize(static_cast<size_t>(n));
    vsnprintf(buf.data(), buf.size() + 1, fmt, args2);
    va_end(args2);

    cerr.write(buf.data(), static_cast<streamsize>(buf.size()));
    cerr.put('\n');
    cerr.flush();
}

inline void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
inline void debug_out(Head H, Tail... T)
{
    cerr << " " << to_string(H);
    debug_out(T...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)