#pragma once

#include "Exceptions/GameException.hpp"
#include "Exceptions/StopProcessingException.hpp"

/*
   \brief An action class is a wrapper around an internal function that may need to have its error handled gracefully.
    In the event that something goes wrong, there are multiple ways to handle, including return a default value,
    run an lambda function with an error code and message paramaters, or throw an exception if the result is not desired in the event of error.

   \note Internally the action class uses cpp::result, a library based on the C++23 standard library 'result_of' function.
   \note The specified type can only be one that has a default constructor.

   \tparam Ret The return type of the calling function
*/
template <typename Ret, typename Err = int>
    requires std::is_default_constructible_v<Ret> || std::is_same_v<Ret, void>
class Action
{
        cpp::result<Ret, Err> result;

    public:
        // ReSharper disable once CppNonExplicitConvertingConstructor
        Action(cpp::result<Ret, Err> res) : result(res) {}

        /*
            \brief Return the value of the called function that is of type Ret. If no param is provided, and the function errored when called
            this will cause a GameException to be thrown. If a std::function of type bool(Error, std::wstring_view) is provided, this will be called
            instead of an exception being raised.

            \param func A lambda that allowed errors to be handled gracefully rather than throwing an exception. It will be called in the event of an error
           being present. If the lambda is executed and returns false, a StopProcessingException will be raised. If true is returned, then processing will
           continue.
            \exception GameException A game exception is raised when Handle is called without a parameter and the called function errors.
            \exception StopProcessingException A stop processing exception is raised when Handle is called with a provided lambda and when called it returns
            false.
        */
        Ret Handle(const std::optional<std::function<bool(Err, std::wstring_view)>>& func = std::nullopt)
        {
            constexpr bool returnTypeIsVoid = std::is_same_v<Ret, void>;

            if (result.has_error())
            {
                // TODO: Handle various error strings
                if (!func.has_value())
                {
#ifdef SERVER
                    throw GameException(L"An error has occurred.", result.error());
#else
                    throw GameException(std::format(L"An error has occured. {}", result.error()));
#endif
                }

                if (!func.value()(result.error(),
#ifdef SERVER
                                  ErrorInfo::GetText(result.error())
#else
                                  L"An error has occured."
#endif
                                      ))
                {
                    throw StopProcessingException();
                }

                if constexpr (returnTypeIsVoid)
                {
                    return;
                }
                else
                {
                    return Ret();
                }
            }

            return result.value();
        }

        /*
            \brief Return the value of the underlying return type. If the called function errored, the default constructor for the specified type will be called
           instead.
        */
        Ret Unwrap()
        {
            if constexpr (std::is_same_v<Ret, void>)
            {
                static_assert(!std::is_same_v<Ret, void>, "Using unwrap of an Action<void, Error> is illogical and malformed.");
                return;
            }
            else
            {
                return result.value_or(Ret());
            }
        }

        /*
            \brief Returns the underlying internal error object. This is not recommended for standard usage and consumption of functions
            and is designed to only be used internally.
        */
        const cpp::result<Ret, Err>& Raw() { return result; }
};
