#pragma once

template <typename T>
class ResourcePtr
{
        std::weak_ptr<T> underlyingPtr;
        std::function<bool(std::shared_ptr<T>)> validator;

    public:
        ResourcePtr(std::weak_ptr<T> ptr, const std::function<bool(std::shared_ptr<T>)>& validator) : underlyingPtr(std::move(ptr)), validator(validator) {}
        ResourcePtr(std::shared_ptr<T> ptr, const std::function<bool(std::shared_ptr<T>)>& validator) : underlyingPtr(ptr), validator(validator) {}

        // Represents a nullptr
        ResourcePtr() {}

        std::shared_ptr<T> Acquire()
        {
            auto ptr = underlyingPtr.lock();
            if (!ptr || !validator(ptr))
            {
                return {};
            }

            return ptr;
        }
};