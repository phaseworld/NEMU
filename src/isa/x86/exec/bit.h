static inline def_EHelper(bsf) {
#ifndef __ENGINE_interpreter__
  panic("not support in engines other than interpreter");
#endif

  rtl_setrelopi(s, RELOP_EQ, s0, dsrc1, 0);
  rtl_set_ZF(s, s0);

  int bit = 0;
  if (*dsrc1 != 0) {
    while ((*dsrc1 & (1u << bit)) == 0) bit++;
    *ddest = bit;
  } else if (s->isa.rep_flags) {
    *ddest = 32;
  }
  operand_write(s, id_dest, ddest);
  print_asm_template2(bsf);
}

static inline def_EHelper(bsr) {
#ifndef __ENGINE_interpreter__
  panic("not support in engines other than interpreter");
#endif

  rtl_setrelopi(s, RELOP_EQ, s0, dsrc1, 0);
  rtl_set_ZF(s, s0);

  int bit = 31;
  if (*dsrc1 != 0) {
    while ((*dsrc1 & (1u << bit)) == 0) bit--;
    *ddest = bit;
    operand_write(s, id_dest, ddest);
  }
  print_asm_template2(bsr);
}

static inline def_EHelper(bt) {
  rtl_li(s, s0, 1);
  rtl_shl(s, s0, s0, dsrc1);
  rtl_and(s, s0, s0, ddest);
  rtl_setrelopi(s, RELOP_NE, s0, s0, 0);
  rtl_set_CF(s, s0);
  print_asm_template2(bt);
}

static inline def_EHelper(btc) {
  rtl_li(s, s0, 1);
  rtl_shl(s, s0, s0, dsrc1);
  rtl_and(s, s1, s0, ddest);
  rtl_setrelopi(s, RELOP_NE, s1, s1, 0);
  rtl_set_CF(s, s1);
  rtl_xor(s, ddest, ddest, s0);
  operand_write(s, id_dest, ddest);
  print_asm_template2(btc);
}

static inline def_EHelper(bts) {
  rtl_li(s, s0, 1);
  rtl_shl(s, s0, s0, dsrc1);
  rtl_and(s, s1, s0, ddest);
  rtl_setrelopi(s, RELOP_NE, s1, s1, 0);
  rtl_set_CF(s, s1);
  rtl_or(s, ddest, ddest, s0);
  operand_write(s, id_dest, ddest);
  print_asm_template2(bts);
}

static inline def_EHelper(btr) {
  rtl_li(s, s0, 1);
  rtl_shl(s, s0, s0, dsrc1);
  rtl_and(s, s1, s0, ddest);
  rtl_setrelopi(s, RELOP_NE, s1, s1, 0);
  rtl_set_CF(s, s1);
  rtl_not(s, s0, s0);
  rtl_and(s, ddest, ddest, s0);
  operand_write(s, id_dest, ddest);
  print_asm_template2(btr);
}

static inline def_EHelper(bswap) {
  // src[7:0]
  rtl_shli(s, s1, ddest, 24);

  // src[31:24]
  rtl_shri(s, s0, ddest, 24);
  rtl_or(s, s1, s1, s0);

  // src[15:8]
  rtl_shli(s, s0, ddest, 8);
  rtl_andi(s, s0, s0, 0xff0000);
  rtl_or(s, s1, s1, s0);

  // src[23:16]
  rtl_shri(s, s0, ddest, 8);
  rtl_andi(s, s0, s0, 0xff00);
  rtl_or(s, ddest, s1, s0);

  operand_write(s, id_dest, ddest);

  print_asm_template1(bswap);
}