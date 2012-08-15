#pragma once

namespace chronotext
{
    class SeedProvider
    {
    public:
        virtual void initSeed(uint32_t seed) = 0;
        virtual uint32_t nextSeed() = 0;
    };
}

namespace chr = chronotext;
