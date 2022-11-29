#pragma once

#include <string>
#include <vector>
#include <iostream>

class CsvFormatter {
public:
    typedef std::string element;
    typedef std::vector<element> row;
    typedef std::vector<row> grid;

public:
    CsvFormatter(int columns, int rows) : header(columns), content(rows, std::vector<std::string>(columns)) {}

public:
    row& operator()() { return header; }
	const row& operator()() const { return header; }
    // operator row&() { return header; }
	// operator const row&() const { return header; }
    std::string& operator()(unsigned i) { return header[i]; }
    const std::string& operator()(unsigned i) const { return header[i]; }
    row& operator[](unsigned i) { return content[i]; }
    const row& operator[](unsigned i) const { return content[i]; }

public:
    row& get_header() { return header; }
    const row& get_header() const { return header; }
    
public:
    friend std::ostream& operator<<(std::ostream& out, const CsvFormatter& cf) {
        for (unsigned i = 0; i < cf().size(); ++i) {
            out << cf(i) << (",\n"[i == cf().size() - 1]);
        }
        for (auto& r : cf.content) {
            for (unsigned i = 0; i < r.size(); ++i) {
                out << r[i] << (",\n"[i == r.size() - 1]);
            }
        }
        return out;
    }
    

private:
    row header;
    grid content;
};