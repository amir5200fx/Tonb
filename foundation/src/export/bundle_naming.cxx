//
// Created by amir on 05/03/2026.
//
#include <tonb/foundation/export/bundle_naming.hxx>

#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace tonb::foundation::exporting {
    namespace {
        std::string sanitise(std::string s) {
            for (char& c : s) {
                if (std::isalnum(static_cast<unsigned char>(c)))
                    continue;
                if (c == '-' || c == '_')
                    continue;
                c = '_';
            }

            // collapse repeated underscores
            std::string out;
            bool last_underscore = false;
            for (char c : s) {
                if (c == '_') {
                    if (!last_underscore)
                        out.push_back(c);
                    last_underscore = true;
                } else {
                    out.push_back(c);
                    last_underscore = false;
                }
            }

            return out;
        }

        void require_non_empty(const std::string& s, const char* name) {
            if (s.empty())
                throw std::invalid_argument(std::string(name) + " is empty");
        }
    }


    std::string make_bundle_name(std::string utc, std::string ns, std::string command,
        std::string input_tag, std::vector<std::string> extra_tags, NamingConfig cfg) {
        require_non_empty(utc, "utc");
        require_non_empty(ns, "namespace");
        require_non_empty(command, "command");

        // ISO8601 compact format validation (basic)
        if (utc.size() != 16 || utc.back() != 'Z')
            throw std::invalid_argument("utc must be YYYYMMDDTHHMMSSZ");

        ns = sanitise(ns);
        command = sanitise(command);
        input_tag = sanitise(input_tag);

        for (auto& t : extra_tags)
            t = sanitise(t);

        std::sort(extra_tags.begin(), extra_tags.end());

        std::string name = utc;
        name += "_";
        name += ns;
        name += "-";
        name += command;

        if (!input_tag.empty()) {
            name += "_";
            name += input_tag;
        }

        if (!extra_tags.empty()) {
            name += "__";
            for (std::size_t i = 0; i < extra_tags.size(); ++i) {
                if (i) name += "_";
                name += extra_tags[i];
            }
        }

        if (name.size() > cfg.max_length) {
            name = name.substr(0, cfg.max_length);
        }

        return name;
    }
}