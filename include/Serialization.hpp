#ifndef SERIALIZE
#define SERIALIZE

#include <fstream>
#include <nlohmann/json.hpp>

#include "refl.hpp"

#ifndef FLHOOK
	#include "FLHook.h"
#endif

template<typename T>
constexpr auto IsBool = std::is_same_v<T, bool>;
template<typename T>
constexpr auto IsInt = std::is_same_v<T, int> || std::is_same_v<T, uint>;
template<typename T>
constexpr auto IsFloat = std::is_same_v<T, float>;
template<typename T>
constexpr auto IsString = std::is_same_v<T, std::string>;
template<typename T>
constexpr auto IsWString = std::is_same_v<T, std::wstring>;
template<typename T>
constexpr auto IsReflectable = std::is_base_of_v<Reflectable, T>;

template<typename>
struct IsVector : std::false_type
{
};
template<typename T, typename A>
struct IsVector<std::vector<T, A>> : std::true_type
{
};
template<typename T, typename TT>
constexpr auto IsVectorOfType = std::is_same_v<T, std::vector<TT>>;

template<typename>
struct IsMap : std::false_type
{
};
template<typename T, typename A>
struct IsMap<std::map<T, A>> : std::true_type
{
};
template<typename T, typename TT, typename TTT>
constexpr auto IsMapOfType = std::is_same_v<T, std::map<TT, TTT>>;

class Serializer
{
	template<typename T>
	static void ReadObject(nlohmann::json& json, T& obj)
	{
		constexpr auto type = refl::reflect<T>();

		refl::util::for_each(type.members, [&type, &obj, &json](auto member) {
			// We ignore static and constant values.
			// Not going to report this as there are use cases where you might want to store constant/static data with
			// the regular
			if (member.is_static || !member.is_writable)
				return;

			// Get our type with the reference removed
			typedef std::remove_reference_t<decltype(member(obj))> DeclType;

			void* ptr = PVOID(std::addressof(obj.*member.pointer));

			// Key if our json key exists. If it doesn't we don't care.
			if (!json.contains(member.name.c_str()))
			{
				// Not found
				return;
			}

			if constexpr (IsBool<DeclType>)
			{
				*static_cast<bool*>(ptr) = json[member.name.c_str()].template get<bool>();
			}
			else if constexpr (IsInt<DeclType>)
			{
				*static_cast<int*>(ptr) = json[member.name.c_str()].template get<int>();
			}
			else if constexpr (IsFloat<DeclType>)
			{
				*static_cast<float*>(ptr) = json[member.name.c_str()].template get<float>();
			}
			else if constexpr (IsString<DeclType>)
			{
				*static_cast<std::string*>(ptr) = json[member.name.c_str()].template get<std::string>();
			}
			else if constexpr (IsWString<DeclType>)
			{
				*static_cast<std::wstring*>(ptr) = stows(json[member.name.c_str()].template get<std::string>());
			}
			else if constexpr (IsReflectable<DeclType>)
			{
				nlohmann::json jObj = json[member.name.c_str()].template get<nlohmann::json::object_t>();
				DeclType reflectable;
				ReadObject(jObj, reflectable);
				*static_cast<DeclType*>(ptr) = reflectable;
			}
			else if constexpr (IsVector<DeclType>::value)
			{
				if constexpr (IsBool<typename DeclType::value_type>)
				{
					*static_cast<std::vector<bool>*>(ptr) = json[member.name.c_str()].template get<std::vector<bool>>();
				}
				else if constexpr (IsInt<typename DeclType::value_type>)
				{
					*static_cast<std::vector<int>*>(ptr) = json[member.name.c_str()].template get<std::vector<int>>();
				}
				else if constexpr (IsFloat<typename DeclType::value_type>)
				{
					*static_cast<std::vector<float>*>(ptr) = json[member.name.c_str()].template get<std::vector<float>>();
				}
				else if constexpr (IsString<typename DeclType::value_type>)
				{
					*static_cast<std::vector<std::string>*>(ptr) = json[member.name.c_str()].template get<std::vector<std::string>>();
				}
				else if constexpr (IsWString<typename DeclType::value_type>)
				{
					std::vector<std::string> vectorOfString = json[member.name.c_str()].template get<std::vector<std::string>>();
					std::vector<std::wstring> vectorOfWstring(vectorOfString.size());
					for (auto& i : vectorOfString)
					{
						vectorOfWstring.emplace_back(stows(i));
					}
					*static_cast<std::vector<std::wstring>*>(ptr) = vectorOfWstring;
				}
				else if constexpr (IsReflectable<typename DeclType::value_type>)
				{
					auto jArr = json[member.name.c_str()].template get<nlohmann::json::array_t>();
					auto declArr = std::vector<DeclType>();
					for (nlohmann::json::iterator iter = jArr.begin(); iter != jArr.end(); ++jArr)
					{
						DeclType reflectable;
						ReadObject(*iter, reflectable);
						declArr.emplace_back(reflectable);
					}

					*static_cast<std::vector<DeclType>>(ptr) = declArr;
				}
				else
				{
					Console::ConWarn(
					    L"Non-reflectable property (%s) present within vector on %s.", stows(member.name.str()).c_str(), stows(type.name.str()).c_str());
				}
			}
			else if constexpr (IsMap<DeclType>::value)
			{
#define GetWide(T)                                                                                      \
	std::map<std::string, T> sMap = json[member.name.c_str()].template get<std::map<std::string, T>>(); \
	std::map<std::wstring, T> wMap;                                                                     \
	for (const auto& [key, value] : sMap)                                                               \
		wMap[stows(key)] = value;                                                                       \
	*static_cast<std::map<std::wstring, T>*>(ptr) = wMap
				if constexpr (IsWString<typename DeclType::value_type::first_type> || IsString<typename DeclType::value_type::first_type>)
				{
					constexpr bool IsWide = IsWString<typename DeclType::value_type::first_type>;
					if constexpr (IsBool<typename DeclType::value_type::second_type>)
					{
						if constexpr (IsWide)
						{
							GetWide(bool);
						}
						else
							*static_cast<std::map<std::string, bool>*>(ptr) = json[member.name.c_str()].template get<std::map<std::string, bool>>();
					}
					else if constexpr (IsInt<typename DeclType::value_type::second_type>)
					{
						if constexpr (IsWide)
						{
							GetWide(int);
						}
						else
							*static_cast<std::map<std::string, int>*>(ptr) = json[member.name.c_str()].template get<std::map<std::string, int>>();
					}
					else if constexpr (IsFloat<typename DeclType::value_type::second_type>)
					{
						if constexpr (IsWide)
						{
							GetWide(float);
						}
						else
							*static_cast<std::map<std::string, float>*>(ptr) = json[member.name.c_str()].template get<std::map<std::string, float>>();
					}
					else if constexpr (IsString<typename DeclType::value_type::second_type>)
					{
						if constexpr (IsWide)
						{
							GetWide(std::string);
						}
						else
							*static_cast<std::map<std::string, std::string>*>(ptr) =
							    json[member.name.c_str()].template get<std::map<std::string, std::string>>();
					}
					else if constexpr (IsWString<typename DeclType::value_type::second_type>)
					{
						std::map<std::string, std::string> mapOfString = json[member.name.c_str()].template get<std::map<std::string, std::string>>();
						if (IsWide)
						{
							std::map<std::wstring, std::wstring> mapOfWstring(mapOfString.size());
							for (auto& i : mapOfString)
							{
								mapOfWstring[stows(i.first)] = stows(i.second);
							}
							*static_cast<std::map<std::wstring, std::wstring>*>(ptr) = mapOfWstring;
						}
						else
						{
							std::map<std::string, std::wstring> mapOfWstring(mapOfString.size());
							for (auto& i : mapOfString)
							{
								mapOfWstring[i.first] = stows(i.second);
							}
							*static_cast<std::map<std::string, std::wstring>*>(ptr) = mapOfWstring;
						}
					}
					else if constexpr (IsReflectable<typename DeclType::value_type::second_type>)
					{
						nlohmann::json::object_t jObj = json[member.name.c_str()].template get<nlohmann::json::object>();
						auto declMap = std::map<std::string, typename DeclType::value_type::second_type>();

						for (auto& i : jObj)
						{
							DeclType reflectable;
							ReadObject(i.second, &reflectable);
							declMap[i.first] = reflectable;
						}
						*static_cast<std::vector<DeclType>>(ptr) = declMap;
					}
				}
#undef GetWide
				else
				{
					Console::ConWarn(L"Key of map (%s) is not a wstring or string.", stows(member.name.str()).c_str());
				}
			}
			else
			{
				Console::ConWarn(L"Non-reflectable property (%s) present on %s.", stows(member.name.str()).c_str(), stows(type.name.str()).c_str());
			}
		});
	}

	template<typename T>
	static void WriteObject(nlohmann::json& json, T& obj)
	{
		constexpr auto type = refl::reflect<T>();
		refl::util::for_each(type.members, [&type, &obj, &json](auto member) {
			// We ignore static and constant values.
			// Not going to report this as there are use cases where you might want to store constant/static data with
			// the regular
			if (member.is_static || !member.is_writable)
				return;

			// Get our type with the reference removed
			typedef std::remove_reference_t<decltype(member(obj))> DeclType;
			if constexpr (IsBool<DeclType> || IsInt<DeclType> || IsFloat<DeclType> || IsString<DeclType> || IsWString<DeclType>)
			{
				if constexpr (IsWString<DeclType>)
				{
					json[member.name.c_str()] = wstos(member(obj));
				}
				else
				{
					json[member.name.c_str()] = member(obj);
				}
			}
			else if constexpr (IsReflectable<DeclType>)
			{
				auto reflectableJson = nlohmann::json::object();
				WriteObject(reflectableJson, member(obj));
				json[member.name.c_str()] = reflectableJson;
			}
			else if constexpr (IsVector<DeclType>::value)
			{
				if constexpr (IsBool<typename DeclType::value_type> || IsInt<typename DeclType::value_type> || IsFloat<typename DeclType::value_type> ||
				    IsString<typename DeclType::value_type> || IsWString<typename DeclType::value_type>)
				{
					if constexpr (IsWString<typename DeclType::value_type>)
					{
						std::vector<std::string> vectorOfStrings;
						for (std::wstring& i : member(obj))
						{
							vectorOfStrings.emplace_back(wstos(i));
						}
						json[member.name.c_str()] = vectorOfStrings;
					}
					else
					{
						json[member.name.c_str()] = member(obj);
					}
				}
				else if constexpr (IsReflectable<typename DeclType::value_type>)
				{
					std::vector<nlohmann::json::object_t> objects;
					auto arr = member.get();
					for (auto& i : arr)
					{
						auto newObj = nlohmann::json::object();
						WriteObject(newObj, i);
						objects.emplace_back(newObj);
					}
					json[member.name.c_str()] = objects;
				}
				else
				{
					Console::ConWarn(
					    L"Non-reflectable property (%s) present within vector on %s.", stows(member.name.str()).c_str(), stows(type.name.str()).c_str());
				}
			}
			else if constexpr (IsMap<DeclType>::value)
			{
				constexpr bool IsWide = std::is_same_v<class std::basic_string<wchar_t, struct std::char_traits<wchar_t>, class std::allocator<wchar_t>> const,
				    DeclType::value_type::first_type>;
				constexpr bool IsNotWide = std::is_same_v<class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> const,
				    DeclType::value_type::first_type>;
				if constexpr (!IsWide && !IsNotWide)
				{
					Console::ConWarn(L"Non-reflectable property (%s) present on %s.", stows(member.name.str()).c_str(), stows(type.name.str()).c_str());
					return;
				}

				if constexpr (IsReflectable<typename DeclType::value_type::second_type>)
				{
					std::map<std::string, nlohmann::json::object_t> objects;
					auto arr = member.get();
					for (const auto& [key, value] : arr)
					{
						auto newObj = nlohmann::json::object();
						WriteObject(newObj, value);
						if constexpr (IsWide)
						{
							objects[wstos(key)] = value;
						}
						else
						{
							objects[key] = value;
						}
					}
					json[member.name.c_str()] = objects;
				}
				else
				{
					if (IsWide)
					{
						std::map<std::string, typename DeclType::value_type::second_type> map;
						for (const auto& [key, value] : member(obj))
						{
							map[wstos(key)] = value;
						}
						json[member.name.c_str()] = map;
					}
					else
					{
						json[member.name.c_str()] = member(obj);
					}
				}
			}
			else
			{
				Console::ConWarn(L"Non-reflectable property (%s) present on %s.", stows(member.name.str()).c_str(), stows(type.name.str()).c_str());
			}
		});
	}

  public:
	/// <summary>
	/// Save an instance of a class/struct to a JSON file.
	/// Reflectable values are int, uint, bool, float, string, Reflectable, and std::vectors of the previous types.
	/// Exceptions will be thrown for invalid file names.
	/// </summary>
	/// <typeparam name="T">The type you want to save as an JSON file.</typeparam>
	/// <param name="t">The instance of the class you would like to serialize.</param>
	/// <param name="fileToSave">Where you would like to save the file. Defaults to empty string. If empty, the class
	/// meta data will be used.</param>
	template<typename T>
	inline static void SaveToJson(T& t, std::string fileToSave = "")
	{
		static_assert(IsReflectable<T>, "Only classes that inherit from 'Reflectable' can be serialized.");

		// If no file is provided, we can search the class metadata.
		if (fileToSave.empty())
		{
			fileToSave = dynamic_cast<Reflectable&>(t).File();
			if (fileToSave.empty())
			{
				Console::ConErr(L"While trying to serialize, a file, both the metadata of the class and fileName were empty.");
				throw std::invalid_argument("While trying to serialize, a file, both the metadata of the class and fileName were empty.");
			}
		}

		// Create our JSON object to write
		auto json = nlohmann::json::object();

		WriteObject(json, t);

		std::ofstream out(fileToSave);
		if (!out.good() || !out.is_open())
		{
			Console::ConWarn(L"Unable to open %s for writing.", stows(fileToSave).c_str());
			return;
		}

		out << json.dump(4);
		out.close();

		Console::ConInfo(L"JSON Serialized - %s", stows(fileToSave.c_str()));
	}

	template<typename T>
	inline static T JsonToObject(std::string fileName = "", bool createIfNotExist = true)
	{
		static_assert(IsReflectable<T>, "Only classes that inherit from 'Reflectable' can be deserialized.");

		// If we cannot load, we return a default
		T ret;

		// If no file is provided, we can search the class metadata.
		if (fileName.empty())
		{
			fileName = dynamic_cast<Reflectable&>(ret).File();
			if (fileName.empty())
			{
				std::string err = "While trying to deserialize, a file, both the metadata of the class and fileName were empty.";
				Console::ConErr(stows(err));
				throw std::invalid_argument(err);
			}
		}

		bool exists = std::filesystem::exists(fileName);
		if (!exists && !createIfNotExist)
		{
			Console::ConErr(L"Couldn't load JSON File (%s)", fileName.c_str());
			return ret;
		}

		if (!exists)
		{
			// Default constructor
			SaveToJson(ret);
			return ret;
		}

		std::ifstream file(fileName);
		if (!file || !file.is_open() || !file.good())
		{
			Console::ConWarn(L"Unable to open JSON file %s", fileName.c_str());
			return ret;
		}

		try
		{
			// Load data from file.
			std::stringstream buffer;
			buffer << file.rdbuf();
			file.close();
			nlohmann::json json = nlohmann::json::parse(buffer.str());

			ReadObject(json, ret);
		}
		catch (nlohmann::json::parse_error& ex)
		{
			Console::ConErr(L"Unable to process JSON. It could not be parsed. See log for more detail.");
			AddLog(Normal, LogLevel::Info,
			    L"Unable to process JSON file [" + stows(fileName) + L"]. The JSON could not be parsed. EXCEPTION: " + stows(ex.what()));
		}
		catch (nlohmann::json::type_error& ex)
		{
			Console::ConErr(L"Unable to process JSON. It could not be parsed. See log for more detail.");
			AddLog(Normal, LogLevel::Info,
			    L"Unable to process JSON file [" + stows(fileName) + L"]. A type within the JSON object did not match. EXCEPTION: " + stows(ex.what()));
		}
		catch (nlohmann::json::exception& ex)
		{
			Console::ConErr(L"Unable to process JSON. It could not be parsed. See log for more detail.");
			AddLog(Normal, LogLevel::Info, L"Unable to process JSON file [" + stows(fileName) + L"] EXCEPTION: " + stows(ex.what()));
		}

		return ret;
	}
};

#endif
