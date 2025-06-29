/* Copyright (c) 2014-2015, Stanislaw Halik <sthalik@misaki.pl>

 * Permission to use, copy, modify, and/or distribute this
 * software for any purpose with or without fee is hereby granted,
 * provided that the above copyright notice and this permission
 * notice appear in all copies.
 */

#pragma once
#include "export.hpp"

#include "options/options.hpp"
#include "main-settings.hpp"

#ifdef _WIN32
#   include "dinput/keybinding-worker.hpp"
#else
#   include "qxt-mini/QxtGlobalShortcut"
#endif

#include <QObject>

#include <tuple>
#include <vector>
#include <functional>

#if !defined __APPLE__
#   define OTR_HAS_KEY_UP_SUPPORT
#endif

namespace shortcuts_impl {

using namespace options;

class OTR_LOGIC_EXPORT Shortcuts final
{
#ifdef _WIN32
    void receiver(const Key& k);
#endif

public:
    using K =
#ifndef _WIN32
    QxtGlobalShortcut*
#else
    Key
#endif
    ;

    using fun = std::function<void(bool)>;
    using tt = std::tuple<K, fun, bool>;
    using t_key = std::tuple<key_opts&, fun, bool>;
    using t_keys = std::vector<t_key>;
    std::vector<tt> keys;
#ifdef _WIN32
    KeybindingWorker::Token key_token {[this](const Key& k) { receiver(k); }};
#endif

    Shortcuts() = default;
    ~Shortcuts() noexcept;

    void reload(const t_keys& keys_);
private:
    void free_binding(K& key);
    void bind_shortcut(K &key, const key_opts& k, bool held);
};

} // ns shortcuts_impl

using shortcuts_impl::Shortcuts;
