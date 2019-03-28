step(){
	ins = memory_fetch_word(regs[15])
		opc = ins >> 24
		if(opc == LDR){
			adr = ins&0xffff
			if(adr > 1023){
				//quit with error
			}
			reg = (ins >> 16) &0xff
			reg[reg] = memory_fetch_word(adr)
		}
	regs[15] += 4

}
