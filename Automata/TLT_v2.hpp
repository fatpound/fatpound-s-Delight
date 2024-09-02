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

        auto operator = (const TLT_v2& src) -> TLT_v2& = delete;
        auto operator = (TLT_v2&& src)      -> TLT_v2& = delete;
        ~TLT_v2() noexcept(false);


    public:
        [[nodiscard]]
        auto GetWords() const noexcept -> std::vector<std::pair<std::string, bool>>;

        void PrintWords() const;


    protected:


    private:
        struct alignas(64) Node_ final
        {
            explicit Node_(const std::pair<std::string, std::vector<std::string>>& tree);
            explicit Node_(const std::string& str);

            std::vector<Node_*> leaves_;

            std::string item_;
        };


    private:
        [[nodiscard]]
        auto GenerateResults_(std::string init_str = "", std::size_t index = 0u, std::size_t recursed = 0u) const -> std::vector<std::pair<std::string, bool>>;

        [[nodiscard]]
        auto IsTerminal_(const std::string& str) const -> bool;

        void Clear_();


    private:
        std::vector<std::pair<std::string, bool>> m_results_;

        std::vector<Node_*> m_trees_;

        static constexpr auto s_recurse_limit_ = 1u;
    };
}
