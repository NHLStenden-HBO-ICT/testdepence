
// Definieer een structuur voor de data
struct Data
{
    float3 value;
    
    
};

// Definieer een RWStructuredBuffer (lees-schrijf buffer)
RWStructuredBuffer<Data> dataBuffer : register(u0);

[numthreads(256, 1, 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    // Voer de berekening uit op het huidige element
    dataBuffer[id.x].value *= 2;
}
