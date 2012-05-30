# handlers_vle.s - INTC software vector mode example using VLE instructions
# Description:  Creates prolog, epilog for C ISR and enables nested interrupts
# Rev 1.0: April 23, 2004, S Mihalik, 
# Rev 1.1 Aug 2, 2004 SM - delayed writing to EOIR until after disabling EE in epilog
# Rev 1.2 Sept 8 2004 SM - optimized & corrected r3,r4 restore sequence from rev 1.1
# Rev 1.2 Sept 21 2004 SM - optimized by minimizing time interrupts are disabled
# Rev 1.3 Jul  2 2007 SM - Changes for MPC551x and mapped to .ivor_handlers section
# Rev 1.4 Sept 29 2008 SM - Modified for VLE instructions
# Copyright Freescale Semiconductor, Inc. 2007. All rights reserved
                       
# STACK FRAME DESIGN: Depth: 20 words (0xA0, or\ 80 bytes)
#            ************* ______________
#   0x4C     *  GPR12    *    ^
#   0x48     *  GPR11    *    |
#   0x44     *  GPR10    *    |
#   0x40     *  GPR9     *    |
#   0x3C     *  GPR8     *    |
#   0x38     *  GPR7     *  GPRs (32 bit)
#   0x34     *  GPR6     *    |
#   0x30     *  GPR5     *    |
#   0x2C     *  GPR4     *    |
#   0x28     *  GPR3     *    |
#   0x24     *  GPR0     * ___v__________
#   0x20     *  CR       * __CR__________
#   0x1C     *  XER      *    ^
#   0x18     *  CTR      *    |
#   0x14     *  LR       * locals & padding for 16 B alignment
#   0x10     *  SRR1	 *    |
#   0x0C     *  SRR0     *    |
#   0x08     *  padding  * ___v__________
#   0x04     * resvd- LR * Reserved for calling function 
#   0x00     *  SP       * Backchain (same as gpr1 in GPRs)
#            ************* 

  .section .ivor_handlers,text_vle     
  	
  .globl	IVOR4Handler
  .align 16				# Align IVOR handlers on a 16 byte boundary for MPC555x
                		# GHS, Cygnus, Diab(default) use .align 4; Metrowerks .align 16
  
  .equ	INTC_IACKR_PRC0, 0xfff48010	# MPC551x Dual Core: Proc'r 0 Interrupt Acknowledge Reg. addr.
  .equ	INTC_EOIR_PRC0,	 0xfff48018	# MPC551x Dual Core: Proc'r 0 End Of Interrupt Reg. addr.
  .equ	INTC_IACKR, 0xfff48010      # Single Core: Interrupt Acknowledge Reg. addr.
  .equ	INTC_EOIR,	0xfff48018	    # Single Core: End Of Interrupt Reg. addr.
	 
IVOR4Handler:
prolog:                       # PROLOGUE 
  e_stwu  r1, -0x50 (r1)      # Create stack frame and store back chain
  se_stw  r3,  0x28 (r1)      # Store a working register 
                              # Note: use se_ form for r0-7, r24-41 with positive offset
  mfsrr0  r3			      # Store SRR0:1 (must be done before enabling EE)
  se_stw  r3,  0x0C (r1)
  mfsrr1  r3				  	
  se_stw  r3,  0x10 (r1)
                                  # Use lines for appropriate processor, MPC551x or MPC555x:
# NOTE: for Diab, GHS, CodeWarrior 2.4, use 2 of the next 4 lines
# e_lis   r3, INTC_IACKR@ha      # Single core: Read pointer into ISR Vector Table
# e_lwz   r3, INTC_IACKR@l(r3)   # Single core
#  e_lis  r3, INTC_IACKR_PRC0@ha     # MPC551x dual core: Read proc'0 pointer into ISR Vector Table
#  e_lwz  r3, INTC_IACKR_PRC0@l(r3)  # MPC551x dual core

# NOTE: For CodeWarrior v2.3, use 3 of the next 6 lines:
# e_lis   r3, INTC_IACKR_PRC0@h  # MPC551x dual core/CW v2.3: Read proc'0 pointer into ISR Vector Table
# e_or2i  r3, INTC_IACKR_PRC0@l  # MPC551x dual core/CW v2.3
# se_lwz  r3, 0x0(r3)            # MPC551x dual core/CW v2.3  
   e_lis   r3, INTC_IACKR@h      # Single Core/CW v2.3: Read proc'0 pointer into ISR Vector Table
   e_or2i  r3, INTC_IACKR@l      # Single Core/CW v2.3
   se_lwz  r3, 0x0(r3)           # Single Core/CW v2.3 
   
  se_lwz  r3, 0x0(r3)            # Read ISR address from ISR Vector Table using pointer

  wrteei  1                     # Set MSR[EE]=1	(must wait a couple clocks after reading IACKR)
  se_stw  r4,  0x2C (r1)        # Store a second working register
  se_mflr r4                    # Store LR (LR will be used for ISR Vector)
  se_stw  r4,  0x14 (r1)
  se_mtlr r3                    # Store ISR address to LR to use for branching later

  e_stw   r12, 0x4C (r1)        # Store rest of gprs
  e_stw   r11, 0x48 (r1)
  e_stw   r10, 0x44 (r1)
  e_stw   r9,  0x40 (r1)
  e_stw   r8,  0x3C (r1)
  se_stw  r7,  0x38 (r1)
  se_stw  r6,  0x34 (r1)
  se_stw  r5,  0x30 (r1)
  se_stw  r0,  0x24 (r1)	  
  mfcr    r3                    # Store CR
  se_stw  r3,  0x20 (r1)
  mfxer   r3                    # Store XER
  se_stw  r3,  0x1C (r1)
  se_mfctr   r3                    # Store CTR
  se_stw  r3,  0x18 (r1)
									
  se_blrl                       # Branch to ISR, but return here

epilog:                         # EPILOGUE
  se_lwz  r3,  0x14 (r1)        # Restore LR	                    
  se_mtlr r3
  se_lwz  r3,  0x18 (r1)        # Restore CTR
  se_mtctr r3
  se_lwz  r3,  0x1C (r1)        # Restore XER
  mtxer   r3
  se_lwz  r3,  0x20 (r1)        # Restore CR
  mtcrf   0xff, r3
  se_lwz  r0,  0x24 (r1)        # Restore other gprs except working registers
  se_lwz  r5,  0x30 (r1)
  se_lwz  r6,  0x34 (r1)
  se_lwz  r7,  0x38 (r1)
  e_lwz   r8,  0x3C (r1)
  e_lwz   r9,  0x40 (r1)
  e_lwz   r10, 0x44 (r1)
  e_lwz   r11, 0x48 (r1)
  e_lwz   r12, 0x4C (r1)
  mbar    0                     # Ensure store to clear interrupt's flag bit completed
                                # Use one of the following 4 lines:
# e_lis   r3, INTC_EOIR_PRC0@h	# Dual Core/CW v2.3: Load upper half of proc'r 0 EIOR addr to r3
  e_lis   r3, INTC_EOIR@h       # Single Core/CW v2.3: Load upper half of EIOR address to r3
# e_lis   r3, INTC_EOIR_PRC0@ha	# Dual Core: Load upper half of proc'r 0 EIOR addr. to r3
# e_lis   r3, INTC_EOIR@ha      # Single Core: Load upper half of EIOR address to r3

  se_li    r4, 0
  		
  wrteei  0                        # Disable interrupts for rest of handler
  
                                   # Use 1 or 2 of the next appropriate lines:                                
# e_or2i  r3, INTC_EOIR_PRC0@l     # Dual Core/CW v2.3
# se_stw  r4, 0x0(r3)              # Dual Core/CW v2.3 - Write 0 to proc'r 0 INTC_EOIR 
  e_or2i  r3, INTC_EOIR@l          # Single Core/CW v2.3
  se_stw  r4, 0x0(r3)              # Single Core/CW v2.3 - Write 0 to proc'r 0 INTC_EOIR
# e_stw   r4, INTC_EIOR_PRC0@l(r3) # Dual Core - Write 0 to proc'r 0 INTC_EIOR 
# e_stw   r4, INTC_EIOR@l(r3)      # Core/Diab - Write 0 to proc'r 0 INTC_EIOR 
       
  se_lwz   r3,  0x0C (r1)        # Restore SRR0
  mtsrr0  r3
  se_lwz  r3,  0x10 (r1)         # Restore SRR1
  mtsrr1  r3
  se_lwz  r4,  0x2C (r1)         # Restore working registers
  se_lwz  r3,  0x28 (r1)		
  e_add16i r1, r1, 0x50         # Delete stack frame
 
  se_rfi                        # End of Interrupt

