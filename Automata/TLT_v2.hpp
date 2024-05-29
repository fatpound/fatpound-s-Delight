#pragma once

#include <vector>
#include <string>

namespace fatpound::automata
{
    /// <summary>
    /// Total Language Tree parser and unique word generator
    /// </summary>
    class TLT_v2 final
    {
        template <typename T>
        using Vector = std::vector<T>;

        template <typename T1, typename T2>
        using Pair = std::pair<T1, T2>;

        using String = std::string;

    public:
        TLT_v2(const Vector<Pair<String, Vector<String>>>& trees);

        TLT_v2() = delete;
        TLT_v2(const TLT_v2& src) = delete;
        TLT_v2& operator = (const TLT_v2& src) = delete;
        TLT_v2(TLT_v2&& src) = delete;
        TLT_v2& operator = (TLT_v2&& src) = delete;
        ~TLT_v2() noexcept;


    public:
        auto GetWords() const noexcept -> Vector<Pair<String, bool>>;


    protected:


    private:
        struct Node_ final
        {
            Vector<Node_*> leaves_;

            String item_;

            Node_(const Pair<String, Vector<String>>& tree);
            Node_(const String& str);
        };
        

    private:
        auto Generate_(String init_str = {}, std::size_t index = 0u, std::size_t recursed_count = 0u) const->Vector<Pair<String, bool>>;

        bool IsTerminal_(const String& str) const;


    private:
        Vector<Pair<String, bool>> results_;

        Vector<Node_*> trees_;

        static constexpr std::size_t recurse_limit_ = 1u;
    };
}