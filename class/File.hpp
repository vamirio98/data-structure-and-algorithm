/**
 * File.hpp - offer the basic multi-platform file operation
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/11 23:58:15
 */

#ifndef FILE_HPP
#define FILE_HPP

#include <string>

class File {
private:
        std::string pathname{""}; // the file path

public:
        static const std::string separator; // the path separator

public:
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
         * @brief Get the name of the file or directory without the parent path
         *
         * @return The name of the file or directory without the parent path
         */
        std::string get_name();

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
