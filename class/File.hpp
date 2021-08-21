/**
 * File.hpp - offer the multi-platform basic file operation
 *
 * Created by Haoyuan Li on 2021/08/11
 * Last Modified: 2021/08/18 23:53:08
 */

#ifndef FILE_HPP_
#define FILE_HPP_

#include <vector>
#include <string>
#include <ctime>

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

public:
        File() = default;
        File(const File &) = delete;
        File &operator=(const File &) = delete;
        ~File() = default;

        /**
         * @brief Create a new File object by the given path
         *
         * @param pathname the specified path
         */
        File(const std::string &pathname);

        /**
         * @brief Create a new File object by the given parent path and
         *        child path
         *
         * @param parent The parent path
         * @param child The child path
         */
        File(const std::string &parent, const std::string &child);

        /**
         * @brief Bind the File object to an abstract path
         *
         * @param pathname The abstract path
         *
         * @sa unbind()
         */
        void bind(const std::string &pathname);

        /**
         * @brief Unbind the File object
         *
         * @sa bind()
         */
        void unbind();

        /**
         * @brief Check whether the file @pathname exists
         *
         * @param pathname The pathname
         *
         * @return True when the file exists, false when not
         */
        static bool exists(const std::string &pathname);

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
         * @brief Check whether the file is a directory
         *
         * @return True if it exists and it's a directory, false otherwise
         */
        bool is_directory() const;

        /**
         * @brief Check whether the file @pathname is a hidden file
         *
         * @param pathname The pathname
         *
         * @return True if it's a hidden file, false otherwise
         */
        static bool is_hidden(const std::string &pathname);

        /**
         * @brief Check whether the file is a hidden file
         *
         * @return True if it's a hidden file, false otherwise
         */
        bool is_hidden() const;

        /**
         * @brief Get the name of the file @pathname without the parent path
         *
         * @param pathname The pathname
         *
         * @return The name of the file without the parent path
         */
        static std::string get_name(const std::string &pathname);

        /**
         * @brief Get the name of the file without the parent path
         *
         * @return The name of the file without the parent path
         */
        std::string get_name() const;

        /**
         * @brief Get the name of the parent path
         *
         * @param pathname The pathname
         *
         * @return The name of the parent path, "" if not found
         */
        static std::string get_parent(const std::string &pathname);

        /**
         * @brief Get the path of file
         *
         * @return The path
         */
        std::string get_path() const;

        /**
         * @brief Get the canonicalized absolute path
         *
         * @param pathname The pathname
         *
         * @return The canonicalized absolute path
         */
        static std::string get_absolute_path(const std::string &pathname);

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

        /**
         * @brief Get the last-modified time
         *
         * @param pathname The file pathname
         *
         * @return The last-modified time representing the number of seconds
         *         elapsed since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)
         *         when successed, 0 when failed
         */
        static time_t last_modified(const std::string &pathname);

        /**
         * @brief Get the last-modified time
         *
         * @return The last-modified time representing the number of seconds
         *         elapsed since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)
         *         when successed, 0 when failed
         */
        time_t last_modified() const;

        /**
         * @brief Get the time string
         *
         * @param t The number of seconds elapsed since the Epoch, 1970-01-01
         *          00:00:00 +0000 (UTC)
         * @param format The time format, the same as strftime(), default:
         *               "%a %b %d %H:%M:%S %Y"
         *
         * @return The time string, default format: Www Mmm dd hh:mm:ss yyyy
         */
        static std::string get_time_str(const time_t &t, const std::string
                        &format = std::string{"%a %b %d %H:%M:%S %Y"});

        /**
         * @brief Get the file @pathname's size
         *
         * @param pathname The file pathname
         *
         * @return The file size in bytes, 0 when the file not exists or it's a
         *         directory
         */
        static long get_size(const std::string &pathname);

        /**
         * @brief Get the file size
         *
         * @return The file size in bytes, 0 when the file not exists or it's a
         *         directory
         */
        long get_size() const;

        /**
         * @brief Check if the file @pathname is readable
         *
         * @param pathname The file pathname
         *
         * @return True when file is readable, false when not
         */
        static bool can_read(const std::string &pathname);

        /**
         * @brief Check if the file is readable
         *
         * @return True when file is readable, false when not
         */
        bool can_read() const;

        /**
         * @brief Check if the file @pathname is writable
         *
         * @param pathname The file pathname
         *
         * @return True when file is writable, false when not
         */
        static bool can_write(const std::string &pathname);

        /**
         * @brief Check if the file is writable
         *
         * @return True when file is writable, false when not
         */
        bool can_write() const;

        /**
         * @brief Check if the file is executable
         *
         * @param pathname The file pathname
         *
         * @return True when file is executable, false when not
         */
        static bool can_execute(const std::string &pathname);

        /**
         * @brief Check if the file is executable
         *
         * @return True when file is executable, false when not
         */
        bool can_execute() const;

        /**
         * @brief List all files and subdirectories in the directory
         *
         * @param pathname The directory path
         *
         * @return The file list vector, or void vector when the file is not
         *         exists or is not a directory
         */
        static std::vector<std::string> list(const std::string &pathname);

        /**
         * @brief List all files and subdirectories in the directory
         *
         * @return The file list vector, or void vector when the file is not
         *         exists or is not a directory
         */
        std::vector<std::string> list() const;

        /**
         * @brief Get the extension of file @pathname
         *
         * @param pathname The pathname
         *
         * @return The extension, "" when not found
         */
        static std::string get_extension(const std::string &pathname);

        /**
         * @brief Get the extension of the file
         *
         * @return The extension, "" when not found
         */
        std::string get_extension() const;

        /**
         * @brief Create a new file
         *
         * @param pathname The name of the new file
         *
         * @return True if the file does not exist and successfully created,
         *         false if the named file already exists or can not create
         */
        static bool create_new_file(const std::string &pathname);

        /**
         * @brief Create a new file
         *
         * @return True if the file does not exist and successfully created,
         *         false if the named file already exists or can not create
         */
        bool create_new_file();

        /**
         * @brief Remove a file or an empty directory
         *
         * @param pathname The name of the file or directory to remove
         *
         * @return Ture if and only if the file or directory is successfully
         *         removed, false otherwise
         */
        static bool remove(const std::string &pathname);

        /**
         * @brief Remove a file or an empty directory
         *
         * @return Ture if and only if the file or directory is successfully
         *         removed, false otherwise
         */
        bool remove();

#if defined(__unix__)
        /**
         * @brief Crete a directory with the specified permission
         *
         * @param pathname The name of the directory to create
         * @param mode The permission, default: 0755
         *
         * @return Ture when directory was created, false otherwise
         */
        static bool mkdir(const std::string &pathname, mode_t mode = 0755);

        /**
         * @brief Crete a directory
         *
         * @param mode The permission, default: 0755
         *
         * @return Ture when directory was created, false otherwise
         */
        bool mkdir(mode_t mode = 0755);
#elif defined(_MSC_VER)
        /**
         * @brief Crete a directory with the specified permission
         *
         * @param pathname The name of the directory to create
         *
         * @return Ture when directory was created, false otherwise
         */
        static bool mkdir(const std::string &pathname);

        /**
         * @brief Crete a directory
         *
         * @return Ture when directory was created, false otherwise
         */
        bool mkdir();
#endif

        /**
         * @brief Move a file or directory
         *
         * @param src The source pathname
         * @param dest The destination pathname
         *
         * @return True when move file or directory successfully,
         *         false otherwise
         */
        static bool move(const std::string &src, const std::string &dest);

        /**
         * @brief Move a file or directory
         *
         * @param dest The destination pathname
         *
         * @return True when move file or directory successfully,
         *         false otherwise
         */
        bool move(const std::string &dest);

private:
        /**
         * @brief Get the last separator in the pathname
         *
         * @return The index of the last separator, std::string::npos if not
         *         found
         *
         * @sa get_error()
         */
        std::string::size_type find_last_separator() const;
};

#endif
