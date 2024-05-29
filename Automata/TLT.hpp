#pragma once

#include <vector>
#include <string>

namespace fatpound::automata
{
    /// <summary>
    /// Total Language Tree parser and full word generator
    /// </summary>
    class TLT final
    {
        template <typename T>
        using Vector = std::vector<T>;

        template <typename T1, typename T2>
        using Pair = std::pair<T1, T2>;

        using String = std::string;

    public:
        TLT(const Vector<Pair<String, Vector<String>>>& cfgs);

        TLT() = delete;
        TLT(const TLT& src) = delete;
        TLT& operator = (const TLT& src) = delete;
        TLT(TLT&& src) = delete;
        TLT& operator = (TLT&& src) = delete;
        ~TLT() noexcept;


    public:
        auto GetWords() const noexcept -> const Vector<String>&;


    protected:


    private:
        struct Node_ final
        {
            Vector<Node_*> leaves_;

            String item_;

            Node_(const String& item);
        };


    private:
        static bool IsTerminal_(const String& word) noexcept;


    private:
        void CreateTree_(Node_* node);
        void CreateInnerTree_(Node_* node);


    private:
        const Vector<Pair<String, Vector<String>>>& cfgs_;
        Vector<String> results_;

        Vector<std::size_t> recurse_;

        Node_* tree_ = nullptr;

        static constexpr std::size_t recurse_limit_ = 1u;
    };
}