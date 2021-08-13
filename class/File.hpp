/**
 * File.hpp - offer the basic multi-platform file operation
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/13 16:56:33
 */

#ifndef FILE_HPP
#define FILE_HPP

#include <string>

class File {
private:
        std::string pathname_{""}; // the file path

public:
        static const std::string separator; // the path separator

        /**
         * @brief Get the last separator in the @pathname
         *
         * @param pathname The pathname
         *
         * @return The index of the last separator, std::string::npos if not
         *         found
         */
        static std::string::size_type find_last_separator(
                        const std::string &pathname);

        /**
         * @brief Check whether the file @pathname exists
         *
         * @param pathname The pathname
         *
         * @return True when the file exists, false when not
         */
        static bool exists(const std::string &pathname);

        /**
         * @brief Check whether the file @pathname is a file
         *
         * @param pathname The pathname
         *
         * @return True if it exists and it's a file, false otherwise
         */
        static bool is_file(const std::string &pathname);

        /**
         * @brief Check whether the file @pathname is a directory
         *
         * @param pathname The pathname
         *
         * @return True if it exists and it's a directory, false otherwise
         */
        static bool is_directory(const std::string &pathname);

        /**
         * @brief Check whether the file @pathname is a hidden file
         *
         * @param pathname The pathname
         *
         * @return True if it's a hidden file, false otherwise
         */
        static bool is_hidden(const std::string &pathname);

        /**
         * @brief Get the name of the file @pathname without the parent path
         *
         * @param pathname The pathname
         *
         * @return The name of the file without the parent path
         */
        static std::string get_name(const std::string &pathname);

        /**
         * @brief Get the name of the parent path
         *
         * @param pathname The pathname
         *
         * @return The name of the parent path, "" if not found
         */
        static std::string get_parent(const std::string &pathname);

        /**
         * @brief Get the canonicalized absolute path
         *
         * @param pathname The pathname
         *
         * @return The canonicalized absolute path
         */
        static std::string get_absolute_path(const std::string &pathname);

public:
        File() = default;
        File(const File &) = delete;
        File &operator=(const File &) = delete;
        ~File() = default;

        /**
         * @brief Create a new File instance by the given path
         *
         * @param pathname the specified path
         */
        File(const std::string &pathname);

        /**
         * @brief Create a new File instance by the given parent path and
         *        child path
         *
         * @param parent The parent path
         * @param child The child path
         */
        File(const std::string &parent, const std::string &child);

        /**
         * @brief Check whether the file or directory exists
         *
         * @return True when the file or directory exists, false when not
         */
        bool exists() const;

        /**
         * @brief Check whether the file is a file
         *
         * @return True if it exists and it's a file, false otherwise
         */
        bool is_file() const;

        /**
         * @brief Check whether the file is a directory
         *
         * @return True if it exists and it's a directory, false otherwise
         */
        bool is_directory() const;

        /**
         * @brief Check whether the file is a hidden file
         *
         * @return True if it's a hidden file, false otherwise
         */
        bool is_hidden() const;

        /**
         * @brief Get the name of the file without the parent path
         *
         * @return The name of the file without the parent path
         */
        std::string get_name() const;

        /**
         * @brief Get the name of the parent path
         *
         * @return The name of the parent path, "" if not found
         */
        std::string get_parent() const;

        /**
         * @brief Get the canonicalized absolute path
         *
         * @return The canonicalized absolute path
         */
        std::string get_absolute_path() const;

private:
        /**
         * @brief Get the last separator in the pathname
         *
         * @return The index of the last separator, std::string::npos if not
         *         found
         */
        std::string::size_type find_last_separator() const;
};

#endif
