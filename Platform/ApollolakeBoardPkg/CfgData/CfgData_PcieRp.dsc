## @file
#
#  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

  # !BSF PAGE:{PLT}

  # !BSF PAGES:{PLT_PCIE_RP_CFG_DATA:SIL:"PCIE RP Config Data"}

  # !BSF PAGES:{PLT_PCIE_RP_FEAT:PLT_PCIE_RP_CFG_DATA:"PCIE RP Features"}

  # !BSF PAGES:{PLT_PCIE_RP_CTRL_PIN:PLT_PCIE_RP_CFG_DATA:"PCIE RP Control Pins"}
  # !BSF PAGES:{PLT_PCIE_RP_CTRL_PIN_PWR:PLT_PCIE_RP_CTRL_PIN:"Power Control Pins"}
  # !BSF PAGES:{PLT_PCIE_RP_CTRL_PIN_RST:PLT_PCIE_RP_CTRL_PIN:"Reset Control Pins"}

  # !BSF SUBT:{CFGHDR_TMPL:PCIE_RP_CFG_DATA:0:0}

  # !HDR EMBED:{PCIE_RP_CFG_DATA:TAG_302:START}

  # !BSF SUBT:{PCIERP_TMPL:0 : 0x8B}
  # !BSF SUBT:{PCIERP_TMPL:1 : 0x8F}
  # !BSF SUBT:{PCIERP_TMPL:2 : 0x87}
  # !BSF SUBT:{PCIERP_TMPL:3 : 0x86}
  # !BSF SUBT:{PCIERP_TMPL:4 : 0x83}
  # !BSF SUBT:{PCIERP_TMPL:5 : 0x8E}

  #                                      Power       : Reset
  # !BSF SUBT:{PCIERP_CTRL_PIN_TMPL:0 :  0x6021318A  : 0x0021618E}
  # !BSF SUBT:{PCIERP_CTRL_PIN_TMPL:1 :  0x8021118A  : 0x0020D18A}
  # !BSF SUBT:{PCIERP_CTRL_PIN_TMPL:2 :  0x4000018B  : 0x0020F18A}
  # !BSF SUBT:{PCIERP_CTRL_PIN_TMPL:3 :  0x0000018B  : 0x0022518A}
  # !BSF SUBT:{PCIERP_CTRL_PIN_TMPL:4 :  0x2000018B  : 0x0000018B}
  # !BSF SUBT:{PCIERP_CTRL_PIN_TMPL:5 :  0x0000018B  : 0x0000018B}

  gCfgData.Reserved                       |      * | 0x02 | 0

  # !HDR EMBED:{PCIE_RP_CFG_DATA:TAG_302:END}
