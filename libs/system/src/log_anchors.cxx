//
// Created by amir on 8/21/25.
//
#include <tonb/system/log.hxx>

tonb::system::ISink::~ISink() = default;
tonb::system::FlushableSink::~FlushableSink() = default;
tonb::system::RewindableSink::~RewindableSink() = default;

tonb::system::ConsoleSink::~ConsoleSink() = default;
tonb::system::JsonFileSink::~JsonFileSink() = default;
tonb::system::BufferedTextSink::~BufferedTextSink() = default;