#pragma once

#include "CFG.hpp"

namespace fatpound::automata
{
    class TLT final
    {
    public:
        explicit TLT(const CFG& cfgs);
        explicit TLT(const std::string& inputFilename);

        explicit TLT() = delete;
        explicit TLT(const TLT& src) = delete;
        explicit TLT(TLT&& src) = delete;

        TLT& operator = (const TLT& src) = delete;
        TLT& operator = (TLT&& src) = delete;
        ~TLT() noexcept(false);


    public:
        auto GetWords() const noexcept -> std::vector<std::string>;

        void PrintWords() const;


    protected:


    private:
        struct Node_ final
        {
            Node_(const std::string& item);

            std::vector<Node_*> leaves;

            std::string item;
        };


    private:
        static bool IsTerminal_(const std::string& word) noexcept;


    private:
        void CreateTree_(Node_* node);
        void CreateInnerTree_(Node_* node);

        void Clear_();


    private:
        const std::vector<std::pair<std::string, std::vector<std::string>>>& m_cfgrammar_;

        std::vector<std::string> m_results_;

        std::vector<std::size_t> m_recursers_;

        Node_* m_tree_ = nullptr;

        static constexpr auto s_recurse_limit_ = 1u;
    };
}
