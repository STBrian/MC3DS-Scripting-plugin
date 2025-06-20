#include "Core/Memory.hpp"

#include <string>

#include <CTRPluginFramework.hpp>

namespace CTRPF = CTRPluginFramework;

// ----------------------------------------------------------------------------

//$Core.Memory

// ----------------------------------------------------------------------------

/*
- Reads an unsigned integer of 32 bits from memory
## offset: integer
## return: integer?
### Core.Memory.readU32
*/
static int l_Memory_readU32(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    u32 value = 0;
    if (!CTRPF::Process::Read32(offset, value))
        lua_pushnil(L);
    else
        lua_pushnumber(L, value);
    return 1;
}

/*
- Reads an unsigned integer of 16 bits from memory
## offset: integer
## return: integer?
### Core.Memory.readU16
*/
static int l_Memory_readU16(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    u16 value = 0;
    if (!CTRPF::Process::Read16(offset, value))
        lua_pushnil(L);
    else
        lua_pushnumber(L, value);
    return 1;
}

/*
- Reads an unsigned integer of 8 bits from memory
## offset: integer
## return: integer?
### Core.Memory.readU8
*/
static int l_Memory_readU8(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    u8 value = 0;
    if (!CTRPF::Process::Read8(offset, value))
        lua_pushnil(L);
    else
        lua_pushnumber(L, value);
    return 1;
}

/*
- Reads a float from memory
## offset: integer
## return: number?
### Core.Memory.readFloat
*/
static int l_Memory_readFloat(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    float value = 0;
    if (!CTRPF::Process::ReadFloat(offset, value))
        lua_pushnil(L);
    else
        lua_pushnumber(L, value);
    return 1;
}

/*
- Reads a double from memory
## offset: integer
## return: number?
### Core.Memory.readDouble
*/
static int l_Memory_readDouble(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    double value = 0;
    if (!CTRPF::Process::ReadDouble(offset, value))
        lua_pushnil(L);
    else
        lua_pushnumber(L, value);
    return 1;
}

/*
- Reads a string from memory
## offset: integer
## size: integer
## return: string?
### Core.Memory.readString
*/
static int l_Memory_readString(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    size_t size = (size_t)luaL_checknumber(L, 2);
    std::string value = "";
    if (!CTRPF::Process::ReadString(offset, value, size, CTRPF::StringFormat::Utf8))
        lua_pushnil(L);
    else
        lua_pushstring(L, value.c_str());
    return 1;
}

/*
- Writes an unsigned integer of 32 bits to memory offset
## offset: integer
## value: integer
## return: boolean
### Core.Memory.writeU32
*/
static int l_Memory_writeU32(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    u32 value = (u32)luaL_checknumber(L, 2);
    lua_pushboolean(L, CTRPF::Process::Write32(offset, value));
    return 1;
}

/*
- Writes an unsigned integer of 16 bits to memory offset
## offset: integer
## value: integer
## return: boolean
### Core.Memory.writeU16
*/
static int l_Memory_writeU16(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    u16 value = (u16)luaL_checknumber(L, 2);
    lua_pushboolean(L, CTRPF::Process::Write16(offset, value));
    return 1;
}

/*
- Writes an unsigned integer of 8 bits to memory offset
## offset: integer
## value: integer
## return: boolean
### Core.Memory.writeU8
*/
static int l_Memory_writeU8(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    u8 value = (u8)luaL_checknumber(L, 2);
    lua_pushboolean(L, CTRPF::Process::Write8(offset, value));
    return 1;
}

/*
- Writes a float to memory offset
## offset: integer
## value: number
## return: boolean
### Core.Memory.writeFloat
*/
static int l_Memory_writeFloat(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    float value = (float)luaL_checknumber(L, 2);
    lua_pushboolean(L, CTRPF::Process::WriteFloat(offset, value));
    return 1;
}

/*
- Writes a double to memory offset
## offset: integer
## value: number
## return: boolean
### Core.Memory.writeDouble
*/
static int l_Memory_writeDouble(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    double value = (double)luaL_checknumber(L, 2);
    lua_pushboolean(L, CTRPF::Process::WriteDouble(offset, value));
    return 1;
}

/*
- Writes a string to memory offset
## offset: integer
## s: string
## size: integer
## return: boolean
### Core.Memory.writeString
*/
static int l_Memory_writeString(lua_State *L) {
    u32 offset = (u32)luaL_checknumber(L, 1);
    const char* str = luaL_checkstring(L, 2);
    size_t size = (size_t)luaL_checknumber(L, 3);
    lua_pushboolean(L, CTRPF::Process::WriteString(offset, str, size, CTRPF::StringFormat::Utf8));
    return 1;
}

// ----------------------------------------------------------------------------

static const luaL_Reg memory_functions[] = {
    {"readU32", l_Memory_readU32},
    {"readU16", l_Memory_readU16},
    {"readU8", l_Memory_readU8},
    {"readFloat", l_Memory_readFloat},
    {"readDouble", l_Memory_readDouble},
    {"readString", l_Memory_readString},
    {"writeU32", l_Memory_writeU32},
    {"writeU16", l_Memory_writeU16},
    {"writeU8", l_Memory_writeU8},
    {"writeFloat", l_Memory_writeFloat},
    {"writeDouble", l_Memory_writeDouble},
    {"writeString", l_Memory_writeString},
    {NULL, NULL}
};

// ----------------------------------------------------------------------------

bool Core::Module::RegisterMemoryModule(lua_State *L) {
    lua_getglobal(L, "Core");
    luaC_register_field(L, memory_functions, "Memory");
    lua_pop(L, 1);
    return true;
}