#pragma once

class Hook UnsupportedException final : std::exception
{
    public:
        explicit UnsupportedException() {}
        ~UnsupportedException() noexcept override = default;
        [[nodiscard]]
        const char* what() const override
        {
            return "The action performed is not supported or valid.";
        }
};
