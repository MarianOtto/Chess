#pragma once

#include <cstdint>
#include <string>

class Square{
    public:
        using Index = uint8_t;
        using Bitmap = uint64_t;
    
        Square(Index idx);
    
        static Square fromNotation(std::string notation);
    
        Index index() const;
        Bitmap bit() const;
        std::string notation() const;
    
    private:
        const Index _index;
    };