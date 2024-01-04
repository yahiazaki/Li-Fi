#define Set_Bit(Register,Bit) ( Register |= (1 << Bit) )

#define Clear_Bit(Register,Bit) ( Register &= (~(1 << Bit)) )

#define Get_Bit(Register,Bit) ( Register &= (1 << Bit) )

#define Toggle_Bit(Register,Bit) ( Register = (~(1 << Bit)) )