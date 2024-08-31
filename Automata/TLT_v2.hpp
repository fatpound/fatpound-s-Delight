#pragma once

#include "CFG.hpp"

namespace fatpound::automata
{
    class TLT_v2 final
    {
    public:
        explicit TLT_v2(const CFG& cfgs);
        explicit TLT_v2(const std::string& inputFilename);

        explicit TLT_v2() = delete;
        explicit TLT_v2(const TLT_v2& src) = delete;
        explicit TLT_v2(TLT_v2&& src) = delete;

        TLT_v2& operator = (const TLT_v2& src) = delete;
        TLT_v2& operator = (TLT_v2&& src) = delete;
        ~TLT_v2() noexcept(false);


    public:
        auto GetWords() const noexcept -> std::vector<std::pair<std::string, bool>>;

        void PrintWords() const;


    protected:


    private:
        struct Node_ final
        {
            Node_(const std::pair<std::string, std::vector<std::string>>& tree);
            Node_(const std::string& str);

            std::vector<Node_*> leaves_;

            std::string item_;
        };


    private:
        auto GenerateResults_(std::string init_str = "", std::size_t index = 0u, std::size_t recursed = 0u) const -> std::vector<std::pair<std::string, bool>>;

        bool IsTerminal_(const std::string& str) const;

        void Clear_();


    private:
        std::vector<std::pair<std::string, bool>> m_results_;

        std::vector<Node_*> m_trees_;

        static constexpr auto s_recurse_limit_ = 1u;
    };
}