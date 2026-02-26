#include <isa/encoding.h>
#include <cstring>

namespace isa
{
    std::optional<Instruction> decode8(const std::array<std::uint8_t, 8> &b)
    {
        Op op = static_cast<Op>(b[0]);

        switch (op)
        {
            case Op::NOP:
            case Op::HAULT:
            case Op::MOV_RR:
            case Op::MOV_RI:
            case Op::ADD_RR:
            case Op::ADD_RI:
            case Op::CMP_RR:
            case Op::LD:
            case Op::ST:
            case Op::JMP:
            case Op::JE:
            case Op::JNE:
                break;
            default:
                return std::nullopt;
        }

        std::int32_t imm{};
        std::memcpy(&imm, &b[4], 4); // assuming little-endian

        Instruction out{};
        out.op = op;
        out.a = b[1];
        out.b = b[2];
        out.c = b[3];
        out.imm = imm;
        return out;
    }

    std::array<std::uint8_t, 8> emit(Op op, std::uint8_t a, std::uint8_t b, std::uint8_t c, std::int32_t imm)
    {
        std::array<std::uint8_t, 8> out{};
        out[0] = static_cast<std::uint8_t>(op);
        out[1] = a;
        out[2] = b;
        out[3] = c;
        std::memcpy(&out[4], &imm, 4);
        return out;
    }
};