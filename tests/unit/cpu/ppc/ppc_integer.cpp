/**
 * (c) 2015 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#include "tests/unit/cpu/test_ppu.h"

/**
 * PPC64 Instructions:
 *  - UISA: Integer instructions (Section: 4.2.1)
 */

void PPCTestRunner::addx() {
    // Add
    TEST_INSTRUCTION(test_add, R1, R2, R3, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(add(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_add(0x000000010000FFFFULL, 0x0000000200000001ULL, 0x0000000300010000ULL);
    test_add(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, 0x0000000000000000ULL);
    
    // Add (with condition)
    TEST_INSTRUCTION(test_add_, R1, R2, R3, LT, GT, EQ, SO, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(add_(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(state.cr[0].lt == LT);
        expect(state.cr[0].gt == GT);
        expect(state.cr[0].eq == EQ);
        expect(state.cr[0].so == SO);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_add_(0x000000010000FFFFULL, 0x0000000200000001ULL, 0x0000000300010000ULL, 0,1,0,0);
    test_add_(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, 0x0000000000000000ULL, 0,0,1,0);
    test_add_(0x0000000000000001ULL, 0x7FFFFFFFFFFFFFFFULL, 0x8000000000000000ULL, 1,0,0,0);
}

void PPCTestRunner::addcx() {
    // Add Carrying
    TEST_INSTRUCTION(test_addc, R1, R2, oldCA, R3, newCA, {
        state.r[1] = R1;
        state.r[2] = R2;
        state.xer.ca = oldCA;
        run(addc(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(state.xer.ca == newCA);
    });

    test_addc(0x000000010000FFFFULL, 0x0000000200000001ULL, false, 0x0000000300010000ULL, false);
    test_addc(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, false, 0x0000000000000000ULL, true);
    test_addc(0xFFFFFFFFFFFFFFF0ULL, 0x000000000000000FULL, true,  0xFFFFFFFFFFFFFFFFULL, false);
    test_addc(0x000000000000FFFFULL, 0xFFFFFFFFFFFF0011ULL, true,  0x0000000000000010ULL, true);

    // Add Carrying (with condition)
    TEST_INSTRUCTION(test_addc_, R1, R2, oldCA, R3, newCA, LT, GT, EQ, SO, {
        state.r[1] = R1;
        state.r[2] = R2;
        state.xer.ca = oldCA;
        run(addc_(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(state.cr[0].lt == LT);
        expect(state.cr[0].gt == GT);
        expect(state.cr[0].eq == EQ);
        expect(state.cr[0].so == SO);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(state.xer.ca == newCA);
    });

    test_addc_(0x000000010000FFFFULL, 0x0000000200000001ULL, false, 0x0000000300010000ULL, false, 0,1,0,0);
    test_addc_(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, false, 0x0000000000000000ULL, true,  0,0,1,0);
    test_addc_(0xFFFFFFFFFFFFFFF0ULL, 0x000000000000000FULL, true,  0xFFFFFFFFFFFFFFFFULL, false, 1,0,0,0);
    test_addc_(0x000000000000FFFFULL, 0xFFFFFFFFFFFF0011ULL, true,  0x0000000000000010ULL, true,  0,1,0,0);
}

void PPCTestRunner::addex() {
    // Add Extended
    TEST_INSTRUCTION(test_adde, R1, R2, oldCA, R3, newCA, {
        state.r[1] = R1;
        state.r[2] = R2;
        state.xer.ca = oldCA;
        run(adde(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(state.xer.ca == newCA);
    });

    test_adde(0x000000010000FFFFULL, 0x0000000200000001ULL, false, 0x0000000300010000ULL, false);
    test_adde(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, false, 0x0000000000000000ULL, true);
    test_adde(0x000000000000FFFFULL, 0x0000000000000000ULL, true,  0x0000000000010000ULL, false);
    test_adde(0xFFFFFFFFFFFFFFF0ULL, 0x000000000000000FULL, true,  0x0000000000000000ULL, true);
        
    // Add Extended (with condition)
    TEST_INSTRUCTION(test_adde_, R1, R2, oldCA, R3, newCA, LT, GT, EQ, SO, {
        state.r[1] = R1;
        state.r[2] = R2;
        state.xer.ca = oldCA;
        run(adde_(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(state.cr[0].lt == LT);
        expect(state.cr[0].gt == GT);
        expect(state.cr[0].eq == EQ);
        expect(state.cr[0].so == SO);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(state.xer.ca == newCA);
    });

    test_adde_(0x000000010000FFFFULL, 0x0000000200000001ULL, false, 0x0000000300010000ULL, false, 0,1,0,0);
    test_adde_(0xFFFFFFFFFFFFFFFFULL, 0x0000000000000001ULL, false, 0x0000000000000000ULL, true,  0,0,1,0);
    test_adde_(0x000000000000FFFFULL, 0x0000000000000000ULL, true,  0x0000000000010000ULL, false, 0,1,0,0);
    test_adde_(0xFFFFFFFFFFFFFFFFULL, 0x8000000000000000ULL, true,  0x8000000000000000ULL, true,  1,0,0,0);
}

void PPCTestRunner::addi() {
    // Add Immediate
    TEST_INSTRUCTION(test_addi, RAIndex, RA, SIMM, R2, {
        state.r[RAIndex] = RA;
        run(addi(r2, RAIndex, SIMM));
        expect(state.r[2] == R2);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_addi(r1, 0x000000010000FFFFULL, 0x0001, 0x0000000100010000ULL);
    test_addi(r1, 0x00000000FFFFFFFFULL, 0x0001, 0x0000000100000000ULL);
    test_addi(r1, 0x00000000FFFF0001ULL, 0xFFFF, 0x00000000FFFF0000ULL);
    test_addi(r1, 0xFFFFFFFFFFFFFFFFULL, 0x0001, 0x0000000000000000ULL);
    test_addi(r0, 0x000000010000FFFFULL, 0x0001, 0x0000000000000001ULL);
    test_addi(r0, 0x00000000FFFFFFFFULL, 0xFFFF, 0xFFFFFFFFFFFFFFFFULL);
    test_addi(r0, 0x00000000FFFF0001ULL, 0x0000, 0x0000000000000000ULL);
}

void PPCTestRunner::addic() {
    // Add Immediate
    TEST_INSTRUCTION(test_addic, R1, SIMM, R2, CA, {
        state.r[1] = R1;
        run(addic(r2, r1, SIMM));
        expect(state.r[2] == R2);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(state.xer.ca == CA);
    });

    test_addic(0x000000010000FFFFULL, 0x0001, 0x0000000100010000ULL, false);
    // TODO: test_addic(0x00000000FFFFFFFFULL, 0x0001, 0x0000000100000000ULL, true);
    // TODO: test_addic(0x00000000FFFF0001ULL, 0xFFFF, 0x00000000FFFF0000ULL, false);
    test_addic(0xFFFFFFFFFFFFFFFFULL, 0x0001, 0x0000000000000000ULL, true);
}

void PPCTestRunner::addic_() {
}

void PPCTestRunner::addis() {
}

void PPCTestRunner::addmex() {
}

void PPCTestRunner::addzex() {
}

void PPCTestRunner::andx() {
    // AND
    TEST_INSTRUCTION(test_and_, R1, R2, R3, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(and_(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_and_(0x0000111100001111ULL, 0x1111111100000000ULL, 0x0000111100000000ULL);
    test_and_(0x00000000000000FFULL, 0x000000000000F0F0ULL, 0x00000000000000F0ULL);

    // AND (with condition)
    TEST_INSTRUCTION(test_and__, R1, R2, R3, LT, GT, EQ, SO, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(and__(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(state.cr[0].lt == LT);
        expect(state.cr[0].gt == GT);
        expect(state.cr[0].eq == EQ);
        expect(state.cr[0].so == SO);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_and__(0x00000000FFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0x00000000FFFFFFFFULL, 0,1,0,0);
    test_and__(0xFFFFFFFF00000000ULL, 0x800000000000FFFFULL, 0x8000000000000000ULL, 1,0,0,0);
    test_and__(0xFFFFFFFF00000000ULL, 0x00000000FFFFFFFFULL, 0x0000000000000000ULL, 0,0,1,0);
}

void PPCTestRunner::andcx() {
    // And with Complement
    TEST_INSTRUCTION(test_andc, R1, R2, R3, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(andc(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_andc(0x0000111100001111ULL, 0x1111111100000000ULL, 0x0000000000001111ULL);
    test_andc(0x00000000000000FFULL, 0x000000000000F0F0ULL, 0x000000000000000FULL);

    // And with Complement (with condition)
    TEST_INSTRUCTION(test_andc_, R1, R2, R3, LT, GT, EQ, SO, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(andc_(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(state.cr[0].lt == LT);
        expect(state.cr[0].gt == GT);
        expect(state.cr[0].eq == EQ);
        expect(state.cr[0].so == SO);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_andc_(0x00000000FFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 0,0,1,0);
    test_andc_(0xFFFFFFFF00005555ULL, 0xFFFFFFFFFFFF0000ULL, 0x0000000000005555ULL, 0,1,0,0);
    test_andc_(0xFFFFFFFF00000000ULL, 0x00000000FFFFFFFFULL, 0xFFFFFFFF00000000ULL, 1,0,0,0);
}

void PPCTestRunner::andi_() {
    // AND Immediate
    TEST_INSTRUCTION(test_andi_, R1, UIMM, R2, LT, GT, EQ, SO, {
        state.r[1] = R1;
        run(andi_(r2, r1, UIMM));
        expect(state.r[2] == R2);
        expect(state.cr[0].lt == LT);
        expect(state.cr[0].gt == GT);
        expect(state.cr[0].eq == EQ);
        expect(state.cr[0].so == SO);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_andi_(0x0000FFFFFFFFFFF0ULL, 0x000F, 0x0000000000000000ULL, 0,0,1,0);
    test_andi_(0x0000FFFFFFFFFFFFULL, 0xFFFF, 0x000000000000FFFFULL, 0,1,0,0);
}

void PPCTestRunner::andis_() {
    // AND Immediate Shifted
    TEST_INSTRUCTION(test_andis_, R1, UIMM, R2, LT, GT, EQ, SO, {
        state.r[1] = R1;
        run(andis_(r2, r1, UIMM));
        expect(state.r[2] == R2);
        expect(state.cr[0].lt == LT);
        expect(state.cr[0].gt == GT);
        expect(state.cr[0].eq == EQ);
        expect(state.cr[0].so == SO);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_andis_(0x0000FFFFFFF0FFFFULL, 0x000F, 0x0000000000000000ULL, 0,0,1,0);
    test_andis_(0x0000FFFFFFFFFFFFULL, 0xFFFF, 0x00000000FFFF0000ULL, 0,1,0,0);
}

void PPCTestRunner::cmp() {
}

void PPCTestRunner::cmpi() {
}

void PPCTestRunner::cmpl() {
}

void PPCTestRunner::cmpli() {
}

void PPCTestRunner::cntlzdx() {
}

void PPCTestRunner::cntlzwx() {
}

void PPCTestRunner::divdx() {
}

void PPCTestRunner::divdux() {
}

void PPCTestRunner::divwx() {
}

void PPCTestRunner::divwux() {
}

void PPCTestRunner::eqvx() {
}

void PPCTestRunner::extsbx() {
}

void PPCTestRunner::extshx() {
}

void PPCTestRunner::extswx() {
}

void PPCTestRunner::mulhdx() {
}

void PPCTestRunner::mulhdux() {
}

void PPCTestRunner::mulhwx() {
}

void PPCTestRunner::mulhwux() {
}

void PPCTestRunner::mulldx() {
}

void PPCTestRunner::mulli() {
}

void PPCTestRunner::mullwx() {
}

void PPCTestRunner::nandx() {
}

void PPCTestRunner::negx() {
}

void PPCTestRunner::norx() {
}

void PPCTestRunner::orx() {
    // OR
    TEST_INSTRUCTION(test_or_, R1, R2, R3, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(or_(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_or_(0x0000111100001111ULL, 0x1111111100000000ULL, 0x1111111100001111ULL);
    test_or_(0x00000000000000FFULL, 0x000000000000F0F0ULL, 0x000000000000F0FFULL);

    // OR (with condition)
    TEST_INSTRUCTION(test_or__, R1, R2, R3, LT, GT, EQ, SO, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(or__(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(state.cr[0].lt == LT);
        expect(state.cr[0].gt == GT);
        expect(state.cr[0].eq == EQ);
        expect(state.cr[0].so == SO);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_or__(0x0000FF00FF00FFFFULL, 0x000000FF00FFFFFFULL, 0x0000FFFFFFFFFFFFULL, 0,1,0,0);
    test_or__(0x000000000000FFFFULL, 0x80000000000000FFULL, 0x800000000000FFFFULL, 1,0,0,0);
    test_or__(0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0,0,1,0);
}

void PPCTestRunner::orcx() {
    // OR with Complement
    TEST_INSTRUCTION(test_orc, R1, R2, R3, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(orc(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_orc(0x0000FFFF0000FFFFULL, 0x00000000FFFFFFFFULL, 0xFFFFFFFF0000FFFFULL);
    test_orc(0x00000000000000FFULL, 0xFFFFFFFFFFFF0F0FULL, 0x000000000000F0FFULL);

    // OR with Complement (with condition)
    TEST_INSTRUCTION(test_orc_, R1, R2, R3, LT, GT, EQ, SO, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(orc_(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(state.cr[0].lt == LT);
        expect(state.cr[0].gt == GT);
        expect(state.cr[0].eq == EQ);
        expect(state.cr[0].so == SO);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_orc_(0x0000FF00FF00FFFFULL, 0xFFFFFF00FF000000ULL, 0x0000FFFFFFFFFFFFULL, 0,1,0,0);
    test_orc_(0x000000000000FFFFULL, 0x0FFFFFFFFFFFFF00ULL, 0xF00000000000FFFFULL, 1,0,0,0);
    test_orc_(0x0000000000000000ULL, 0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 0,0,1,0);
}

void PPCTestRunner::ori() {
    // OR Immediate
    TEST_INSTRUCTION(test_ori, R1, UIMM, R2,{
        state.r[1] = R1;
        run(ori(r2, r1, UIMM));
        expect(state.r[2] == R2);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_ori(0x000000000000FF00ULL, 0x0F0F, 0x000000000000FF0FULL);
    test_ori(0x0000FFFFFFFFFFFFULL, 0xFFFF, 0x0000FFFFFFFFFFFFULL);
}

void PPCTestRunner::oris() {
    // OR Immediate Shifted
    TEST_INSTRUCTION(test_oris, R1, UIMM, R2, {
        state.r[1] = R1;
        run(oris(r2, r1, UIMM));
        expect(state.r[2] == R2);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_oris(0x00000000FF0000FFULL, 0x0F0F, 0x00000000FF0F00FFULL);
    test_oris(0x0000FFFFFFFFFF00ULL, 0xFFFF, 0x0000FFFFFFFFFF00ULL);
}

void PPCTestRunner::rldc_lr() {
}

void PPCTestRunner::rldicx() {
}

void PPCTestRunner::rldiclx() {
}

void PPCTestRunner::rldicrx() {
}

void PPCTestRunner::rldimix() {
}

void PPCTestRunner::rlwimix() {
}

void PPCTestRunner::rlwinmx() {
}

void PPCTestRunner::rlwnmx() {
}

void PPCTestRunner::sldx() {
}

void PPCTestRunner::slwx() {
}

void PPCTestRunner::sradx() {
}

void PPCTestRunner::sradix() {
}

void PPCTestRunner::srawx() {
}

void PPCTestRunner::srawix() {
}

void PPCTestRunner::srdx() {
}

void PPCTestRunner::srwx() {
}

void PPCTestRunner::subfx() {
}

void PPCTestRunner::subfcx() {
}

void PPCTestRunner::subfex() {
}

void PPCTestRunner::subfic() {
}

void PPCTestRunner::subfmex() {
}

void PPCTestRunner::subfzex() {
}

void PPCTestRunner::xorx() {
    // XOR
    TEST_INSTRUCTION(test_xor_, R1, R2, R3, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(xor_(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_xor_(0x0000111100001111ULL, 0x1111111100000000ULL, 0x1111000000001111ULL);
    test_xor_(0x00000000000000FFULL, 0x000000000000F0F0ULL, 0x000000000000F00FULL);

    // XOR (with condition)
    TEST_INSTRUCTION(test_xor__, R1, R2, R3, LT, GT, EQ, SO, {
        state.r[1] = R1;
        state.r[2] = R2;
        run(xor__(r3, r1, r2));
        expect(state.r[3] == R3);
        expect(state.cr[0].lt == LT);
        expect(state.cr[0].gt == GT);
        expect(state.cr[0].eq == EQ);
        expect(state.cr[0].so == SO);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_xor__(0x0000FF00FF00FFFFULL, 0x000000FF00FFFFFFULL, 0x0000FFFFFFFF0000ULL, 0,1,0,0);
    test_xor__(0x000000000000FFFFULL, 0x80000000000000FFULL, 0x800000000000FF00ULL, 1,0,0,0);
    test_xor__(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 0,0,1,0);
}

void PPCTestRunner::xori() {
    // XOR Immediate
    TEST_INSTRUCTION(test_xori, R1, UIMM, R2,{
        state.r[1] = R1;
        run(xori(r2, r1, UIMM));
        expect(state.r[2] == R2);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_xori(0x000000000000FF00ULL, 0x0F0F, 0x000000000000F00FULL);
    test_xori(0x0000FFFFFFFFFFFFULL, 0xFFFF, 0x0000FFFFFFFF0000ULL);
}

void PPCTestRunner::xoris() {
    // XOR Immediate Shifted
    TEST_INSTRUCTION(test_xoris, R1, UIMM, R2, {
        state.r[1] = R1;
        run(xoris(r2, r1, UIMM));
        expect(state.r[2] == R2);
        expect(!state.cr[0].lt);
        expect(!state.cr[0].gt);
        expect(!state.cr[0].eq);
        expect(!state.cr[0].so);
        expect(!state.xer.so);
        expect(!state.xer.ov);
        expect(!state.xer.ca);
    });

    test_xoris(0x00000000FF0000FFULL, 0x0F0F, 0x00000000F00F00FFULL);
    test_xoris(0x0000FFFFFFFFFF00ULL, 0xFFFF, 0x0000FFFF0000FF00ULL);
}
