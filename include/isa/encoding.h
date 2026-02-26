#pragma once
#include <array>
#include <cstdint>
#include <optional>

namespace isa 
{
    static constexpr std::size_t kNumRegs = 16;
    static constexpr std::uint64_t kInsnSz = 8;

    enum class Op : std::uint8_t 
    {
        NOP = 0x00,
        HAULT = 0x01,

        MOV_RR = 0x10, // mov a, b  => r[a] = r[b]
        MOV_RI = 0x11, // mov a, imm  => r[a] = imm

        ADD_RR = 0x20, // add a,b  => r[a] = r[a] + r[b]
        ADD_RI = 0x21, // add a, imm  => r[a] = r[a] + imm

        CMP_RR = 0x30, // cmp a,b  => ZF = (r[a] == r[b])

        LD = 0x40, // mov a,[b+imm]  => r[a] = *(u64*)(r[b]+imm)
        ST = 0x41, // mov [a+imm], b  => *(u64*)(r[a]+imm) = r[b]

        JMP = 0x50, // jmp rel32
        JE = 0x51, // je rel32
        JNE = 0x52, // jne rel32
    };

    struct Instruction
    {
        Op op{};

        std::uint8_t a{};
        std::uint8_t b{};
        std::uint8_t c{};
        std::uint8_t imm{};
    };

    std::optional<Instruction> decode8(const std::array<std::uint8_t, 8> &bytes);
    std::array<std::uint8_t, 8> emit(Op op, std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t imm);

} // namespace isa