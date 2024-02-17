#ifndef __MMIO_H__
#define __MMIO_H__

#define write32(val, addr) ({ DMB; (*(volatile u32 *)(addr)=(val)); val; })
#define read32(addr) ({ u32 __v = (*(volatile u32 *)(addr)); DMB; __v; })

#define BIT(nr) (1<<(nr)) 
#define MASK(bit_cnt) ((1ULL<<(bit_cnt))-1)
#define REG_MASK(high, low) (MASK((high)-(low))<<((high)-(low)))

#define set_bit(p, n) ((p)|=(1<<(n)))
#define clr_bit(p, n) ((p)&=~(1<<(n)))

#endif /* __MMIO_H__ */
