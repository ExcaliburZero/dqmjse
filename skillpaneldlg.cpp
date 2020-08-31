
#include "stdafx.h"
#include "dqmjse.h"
#include "skillpaneldlg.h"
#include "skilllibrarydlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

#define ON_ONE_ITEM_CLICKED(idx)	ON_BN_CLICKED(IDC_CHECK_UNLOCK_SKILL[idx], OnBnClickedCheckUnlockSkill<idx>) ON_BN_CLICKED(IDC_BUTTON_ALL_SKILL[idx], OnBnClickedButtonAllSkill<idx>)
#define ON_ANY_ITEM_CLICKED()		ON_ONE_ITEM_CLICKED(0) ON_ONE_ITEM_CLICKED(1) ON_ONE_ITEM_CLICKED(2) ON_ONE_ITEM_CLICKED(3) ON_ONE_ITEM_CLICKED(4) ON_ONE_ITEM_CLICKED(5) ON_ONE_ITEM_CLICKED(6) ON_ONE_ITEM_CLICKED(7) ON_ONE_ITEM_CLICKED(8) ON_ONE_ITEM_CLICKED(9) ON_ONE_ITEM_CLICKED(10) ON_ONE_ITEM_CLICKED(11) ON_ONE_ITEM_CLICKED(12) ON_ONE_ITEM_CLICKED(13) ON_ONE_ITEM_CLICKED(14) ON_ONE_ITEM_CLICKED(15) ON_ONE_ITEM_CLICKED(16) ON_ONE_ITEM_CLICKED(17) ON_ONE_ITEM_CLICKED(18) ON_ONE_ITEM_CLICKED(19) ON_ONE_ITEM_CLICKED(20) ON_ONE_ITEM_CLICKED(21) ON_ONE_ITEM_CLICKED(22) ON_ONE_ITEM_CLICKED(23) ON_ONE_ITEM_CLICKED(24) ON_ONE_ITEM_CLICKED(25) ON_ONE_ITEM_CLICKED(26) ON_ONE_ITEM_CLICKED(27) ON_ONE_ITEM_CLICKED(28) ON_ONE_ITEM_CLICKED(29) ON_ONE_ITEM_CLICKED(30) ON_ONE_ITEM_CLICKED(31) ON_ONE_ITEM_CLICKED(32) ON_ONE_ITEM_CLICKED(33) ON_ONE_ITEM_CLICKED(34) ON_ONE_ITEM_CLICKED(35) ON_ONE_ITEM_CLICKED(36) ON_ONE_ITEM_CLICKED(37) ON_ONE_ITEM_CLICKED(38) ON_ONE_ITEM_CLICKED(39) ON_ONE_ITEM_CLICKED(40) ON_ONE_ITEM_CLICKED(41) ON_ONE_ITEM_CLICKED(42) ON_ONE_ITEM_CLICKED(43) ON_ONE_ITEM_CLICKED(44) ON_ONE_ITEM_CLICKED(45) ON_ONE_ITEM_CLICKED(46) ON_ONE_ITEM_CLICKED(47) ON_ONE_ITEM_CLICKED(48) ON_ONE_ITEM_CLICKED(49) ON_ONE_ITEM_CLICKED(50) ON_ONE_ITEM_CLICKED(51) ON_ONE_ITEM_CLICKED(52) ON_ONE_ITEM_CLICKED(53) ON_ONE_ITEM_CLICKED(54) ON_ONE_ITEM_CLICKED(55) ON_ONE_ITEM_CLICKED(56) ON_ONE_ITEM_CLICKED(57) ON_ONE_ITEM_CLICKED(58) ON_ONE_ITEM_CLICKED(59) ON_ONE_ITEM_CLICKED(60) ON_ONE_ITEM_CLICKED(61) ON_ONE_ITEM_CLICKED(62) ON_ONE_ITEM_CLICKED(63) ON_ONE_ITEM_CLICKED(64) ON_ONE_ITEM_CLICKED(65) ON_ONE_ITEM_CLICKED(66) ON_ONE_ITEM_CLICKED(67) ON_ONE_ITEM_CLICKED(68) ON_ONE_ITEM_CLICKED(69) ON_ONE_ITEM_CLICKED(70) ON_ONE_ITEM_CLICKED(71) ON_ONE_ITEM_CLICKED(72) ON_ONE_ITEM_CLICKED(73) ON_ONE_ITEM_CLICKED(74) ON_ONE_ITEM_CLICKED(75) ON_ONE_ITEM_CLICKED(76) ON_ONE_ITEM_CLICKED(77) ON_ONE_ITEM_CLICKED(78) ON_ONE_ITEM_CLICKED(79) ON_ONE_ITEM_CLICKED(80) ON_ONE_ITEM_CLICKED(81) ON_ONE_ITEM_CLICKED(82) ON_ONE_ITEM_CLICKED(83) ON_ONE_ITEM_CLICKED(84) ON_ONE_ITEM_CLICKED(85) ON_ONE_ITEM_CLICKED(86) ON_ONE_ITEM_CLICKED(87) ON_ONE_ITEM_CLICKED(88) ON_ONE_ITEM_CLICKED(89) ON_ONE_ITEM_CLICKED(90) ON_ONE_ITEM_CLICKED(91) ON_ONE_ITEM_CLICKED(92) ON_ONE_ITEM_CLICKED(93) ON_ONE_ITEM_CLICKED(94) ON_ONE_ITEM_CLICKED(95) ON_ONE_ITEM_CLICKED(96) ON_ONE_ITEM_CLICKED(97) ON_ONE_ITEM_CLICKED(98) ON_ONE_ITEM_CLICKED(99) ON_ONE_ITEM_CLICKED(100) ON_ONE_ITEM_CLICKED(101) ON_ONE_ITEM_CLICKED(102) ON_ONE_ITEM_CLICKED(103) ON_ONE_ITEM_CLICKED(104) ON_ONE_ITEM_CLICKED(105) ON_ONE_ITEM_CLICKED(106) ON_ONE_ITEM_CLICKED(107) ON_ONE_ITEM_CLICKED(108) ON_ONE_ITEM_CLICKED(109) ON_ONE_ITEM_CLICKED(110) ON_ONE_ITEM_CLICKED(111) ON_ONE_ITEM_CLICKED(112) ON_ONE_ITEM_CLICKED(113) ON_ONE_ITEM_CLICKED(114) ON_ONE_ITEM_CLICKED(115) ON_ONE_ITEM_CLICKED(116) ON_ONE_ITEM_CLICKED(117) ON_ONE_ITEM_CLICKED(118) ON_ONE_ITEM_CLICKED(119) ON_ONE_ITEM_CLICKED(120) ON_ONE_ITEM_CLICKED(121) ON_ONE_ITEM_CLICKED(122) ON_ONE_ITEM_CLICKED(123) ON_ONE_ITEM_CLICKED(124) ON_ONE_ITEM_CLICKED(125) ON_ONE_ITEM_CLICKED(126) ON_ONE_ITEM_CLICKED(127) ON_ONE_ITEM_CLICKED(128) ON_ONE_ITEM_CLICKED(129) ON_ONE_ITEM_CLICKED(130) ON_ONE_ITEM_CLICKED(131) ON_ONE_ITEM_CLICKED(132) ON_ONE_ITEM_CLICKED(133) ON_ONE_ITEM_CLICKED(134) ON_ONE_ITEM_CLICKED(135) ON_ONE_ITEM_CLICKED(136) ON_ONE_ITEM_CLICKED(137) ON_ONE_ITEM_CLICKED(138) ON_ONE_ITEM_CLICKED(139) ON_ONE_ITEM_CLICKED(140) ON_ONE_ITEM_CLICKED(141) ON_ONE_ITEM_CLICKED(142) ON_ONE_ITEM_CLICKED(143) ON_ONE_ITEM_CLICKED(144) ON_ONE_ITEM_CLICKED(145) ON_ONE_ITEM_CLICKED(146) ON_ONE_ITEM_CLICKED(147) ON_ONE_ITEM_CLICKED(148) ON_ONE_ITEM_CLICKED(149) ON_ONE_ITEM_CLICKED(150) ON_ONE_ITEM_CLICKED(151) ON_ONE_ITEM_CLICKED(152) ON_ONE_ITEM_CLICKED(153) ON_ONE_ITEM_CLICKED(154) ON_ONE_ITEM_CLICKED(155) ON_ONE_ITEM_CLICKED(156) ON_ONE_ITEM_CLICKED(157) ON_ONE_ITEM_CLICKED(158) ON_ONE_ITEM_CLICKED(159) ON_ONE_ITEM_CLICKED(160) ON_ONE_ITEM_CLICKED(161) ON_ONE_ITEM_CLICKED(162) ON_ONE_ITEM_CLICKED(163) ON_ONE_ITEM_CLICKED(164) ON_ONE_ITEM_CLICKED(165) ON_ONE_ITEM_CLICKED(166) ON_ONE_ITEM_CLICKED(167) ON_ONE_ITEM_CLICKED(168) ON_ONE_ITEM_CLICKED(169) ON_ONE_ITEM_CLICKED(170) ON_ONE_ITEM_CLICKED(171) ON_ONE_ITEM_CLICKED(172) ON_ONE_ITEM_CLICKED(173) ON_ONE_ITEM_CLICKED(174) ON_ONE_ITEM_CLICKED(175) ON_ONE_ITEM_CLICKED(176) ON_ONE_ITEM_CLICKED(177) ON_ONE_ITEM_CLICKED(178) ON_ONE_ITEM_CLICKED(179) ON_ONE_ITEM_CLICKED(180) ON_ONE_ITEM_CLICKED(181) ON_ONE_ITEM_CLICKED(182) ON_ONE_ITEM_CLICKED(183) ON_ONE_ITEM_CLICKED(184) ON_ONE_ITEM_CLICKED(185) ON_ONE_ITEM_CLICKED(186) ON_ONE_ITEM_CLICKED(187) ON_ONE_ITEM_CLICKED(188) ON_ONE_ITEM_CLICKED(189) ON_ONE_ITEM_CLICKED(190) ON_ONE_ITEM_CLICKED(191)

//////////////////////////////////////////////////////////////////////////

const int IDC_LIBRARY_SKILL[]		= { IDC_LIBRARY_SKILL1, IDC_LIBRARY_SKILL2, IDC_LIBRARY_SKILL3, IDC_LIBRARY_SKILL4, IDC_LIBRARY_SKILL5, IDC_LIBRARY_SKILL6, IDC_LIBRARY_SKILL7, IDC_LIBRARY_SKILL8, IDC_LIBRARY_SKILL9, IDC_LIBRARY_SKILL10, IDC_LIBRARY_SKILL11, IDC_LIBRARY_SKILL12, IDC_LIBRARY_SKILL13, IDC_LIBRARY_SKILL14, IDC_LIBRARY_SKILL15, IDC_LIBRARY_SKILL16, IDC_LIBRARY_SKILL17, IDC_LIBRARY_SKILL18, IDC_LIBRARY_SKILL19, IDC_LIBRARY_SKILL20, IDC_LIBRARY_SKILL21, IDC_LIBRARY_SKILL22, IDC_LIBRARY_SKILL23, IDC_LIBRARY_SKILL24, IDC_LIBRARY_SKILL25, IDC_LIBRARY_SKILL26, IDC_LIBRARY_SKILL27, IDC_LIBRARY_SKILL28, IDC_LIBRARY_SKILL29, IDC_LIBRARY_SKILL30, IDC_LIBRARY_SKILL31, IDC_LIBRARY_SKILL32, IDC_LIBRARY_SKILL33, IDC_LIBRARY_SKILL34, IDC_LIBRARY_SKILL35, IDC_LIBRARY_SKILL36, IDC_LIBRARY_SKILL37, IDC_LIBRARY_SKILL38, IDC_LIBRARY_SKILL39, IDC_LIBRARY_SKILL40, IDC_LIBRARY_SKILL41, IDC_LIBRARY_SKILL42, IDC_LIBRARY_SKILL43, IDC_LIBRARY_SKILL44, IDC_LIBRARY_SKILL45, IDC_LIBRARY_SKILL46, IDC_LIBRARY_SKILL47, IDC_LIBRARY_SKILL48, IDC_LIBRARY_SKILL49, IDC_LIBRARY_SKILL50, IDC_LIBRARY_SKILL51, IDC_LIBRARY_SKILL52, IDC_LIBRARY_SKILL53, IDC_LIBRARY_SKILL54, IDC_LIBRARY_SKILL55, IDC_LIBRARY_SKILL56, IDC_LIBRARY_SKILL57, IDC_LIBRARY_SKILL58, IDC_LIBRARY_SKILL59, IDC_LIBRARY_SKILL60, IDC_LIBRARY_SKILL61, IDC_LIBRARY_SKILL62, IDC_LIBRARY_SKILL63, IDC_LIBRARY_SKILL64, IDC_LIBRARY_SKILL65, IDC_LIBRARY_SKILL66, IDC_LIBRARY_SKILL67, IDC_LIBRARY_SKILL68, IDC_LIBRARY_SKILL69, IDC_LIBRARY_SKILL70, IDC_LIBRARY_SKILL71, IDC_LIBRARY_SKILL72, IDC_LIBRARY_SKILL73, IDC_LIBRARY_SKILL74, IDC_LIBRARY_SKILL75, IDC_LIBRARY_SKILL76, IDC_LIBRARY_SKILL77, IDC_LIBRARY_SKILL78, IDC_LIBRARY_SKILL79, IDC_LIBRARY_SKILL80, IDC_LIBRARY_SKILL81, IDC_LIBRARY_SKILL82, IDC_LIBRARY_SKILL83, IDC_LIBRARY_SKILL84, IDC_LIBRARY_SKILL85, IDC_LIBRARY_SKILL86, IDC_LIBRARY_SKILL87, IDC_LIBRARY_SKILL88, IDC_LIBRARY_SKILL89, IDC_LIBRARY_SKILL90, IDC_LIBRARY_SKILL91, IDC_LIBRARY_SKILL92, IDC_LIBRARY_SKILL93, IDC_LIBRARY_SKILL94, IDC_LIBRARY_SKILL95, IDC_LIBRARY_SKILL96, IDC_LIBRARY_SKILL97, IDC_LIBRARY_SKILL98, IDC_LIBRARY_SKILL99, IDC_LIBRARY_SKILL100, IDC_LIBRARY_SKILL101, IDC_LIBRARY_SKILL102, IDC_LIBRARY_SKILL103, IDC_LIBRARY_SKILL104, IDC_LIBRARY_SKILL105, IDC_LIBRARY_SKILL106, IDC_LIBRARY_SKILL107, IDC_LIBRARY_SKILL108, IDC_LIBRARY_SKILL109, IDC_LIBRARY_SKILL110, IDC_LIBRARY_SKILL111, IDC_LIBRARY_SKILL112, IDC_LIBRARY_SKILL113, IDC_LIBRARY_SKILL114, IDC_LIBRARY_SKILL115, IDC_LIBRARY_SKILL116, IDC_LIBRARY_SKILL117, IDC_LIBRARY_SKILL118, IDC_LIBRARY_SKILL119, IDC_LIBRARY_SKILL120, IDC_LIBRARY_SKILL121, IDC_LIBRARY_SKILL122, IDC_LIBRARY_SKILL123, IDC_LIBRARY_SKILL124, IDC_LIBRARY_SKILL125, IDC_LIBRARY_SKILL126, IDC_LIBRARY_SKILL127, IDC_LIBRARY_SKILL128, IDC_LIBRARY_SKILL129, IDC_LIBRARY_SKILL130, IDC_LIBRARY_SKILL131, IDC_LIBRARY_SKILL132, IDC_LIBRARY_SKILL133, IDC_LIBRARY_SKILL134, IDC_LIBRARY_SKILL135, IDC_LIBRARY_SKILL136, IDC_LIBRARY_SKILL137, IDC_LIBRARY_SKILL138, IDC_LIBRARY_SKILL139, IDC_LIBRARY_SKILL140, IDC_LIBRARY_SKILL141, IDC_LIBRARY_SKILL142, IDC_LIBRARY_SKILL143, IDC_LIBRARY_SKILL144, IDC_LIBRARY_SKILL145, IDC_LIBRARY_SKILL146, IDC_LIBRARY_SKILL147, IDC_LIBRARY_SKILL148, IDC_LIBRARY_SKILL149, IDC_LIBRARY_SKILL150, IDC_LIBRARY_SKILL151, IDC_LIBRARY_SKILL152, IDC_LIBRARY_SKILL153, IDC_LIBRARY_SKILL154, IDC_LIBRARY_SKILL155, IDC_LIBRARY_SKILL156, IDC_LIBRARY_SKILL157, IDC_LIBRARY_SKILL158, IDC_LIBRARY_SKILL159, IDC_LIBRARY_SKILL160, IDC_LIBRARY_SKILL161, IDC_LIBRARY_SKILL162, IDC_LIBRARY_SKILL163, IDC_LIBRARY_SKILL164, IDC_LIBRARY_SKILL165, IDC_LIBRARY_SKILL166, IDC_LIBRARY_SKILL167, IDC_LIBRARY_SKILL168, IDC_LIBRARY_SKILL169, IDC_LIBRARY_SKILL170, IDC_LIBRARY_SKILL171, IDC_LIBRARY_SKILL172, IDC_LIBRARY_SKILL173, IDC_LIBRARY_SKILL174, IDC_LIBRARY_SKILL175, IDC_LIBRARY_SKILL176, IDC_LIBRARY_SKILL177, IDC_LIBRARY_SKILL178, IDC_LIBRARY_SKILL179, IDC_LIBRARY_SKILL180, IDC_LIBRARY_SKILL181, IDC_LIBRARY_SKILL182, IDC_LIBRARY_SKILL183, IDC_LIBRARY_SKILL184, IDC_LIBRARY_SKILL185, IDC_LIBRARY_SKILL186, IDC_LIBRARY_SKILL187, IDC_LIBRARY_SKILL188, IDC_LIBRARY_SKILL189, IDC_LIBRARY_SKILL190, IDC_LIBRARY_SKILL191, IDC_LIBRARY_SKILL192 };
const int IDC_CHECK_UNLOCK_SKILL[]	= { IDC_CHECK_UNLOCK_SKILL1, IDC_CHECK_UNLOCK_SKILL2, IDC_CHECK_UNLOCK_SKILL3, IDC_CHECK_UNLOCK_SKILL4, IDC_CHECK_UNLOCK_SKILL5, IDC_CHECK_UNLOCK_SKILL6, IDC_CHECK_UNLOCK_SKILL7, IDC_CHECK_UNLOCK_SKILL8, IDC_CHECK_UNLOCK_SKILL9, IDC_CHECK_UNLOCK_SKILL10, IDC_CHECK_UNLOCK_SKILL11, IDC_CHECK_UNLOCK_SKILL12, IDC_CHECK_UNLOCK_SKILL13, IDC_CHECK_UNLOCK_SKILL14, IDC_CHECK_UNLOCK_SKILL15, IDC_CHECK_UNLOCK_SKILL16, IDC_CHECK_UNLOCK_SKILL17, IDC_CHECK_UNLOCK_SKILL18, IDC_CHECK_UNLOCK_SKILL19, IDC_CHECK_UNLOCK_SKILL20, IDC_CHECK_UNLOCK_SKILL21, IDC_CHECK_UNLOCK_SKILL22, IDC_CHECK_UNLOCK_SKILL23, IDC_CHECK_UNLOCK_SKILL24, IDC_CHECK_UNLOCK_SKILL25, IDC_CHECK_UNLOCK_SKILL26, IDC_CHECK_UNLOCK_SKILL27, IDC_CHECK_UNLOCK_SKILL28, IDC_CHECK_UNLOCK_SKILL29, IDC_CHECK_UNLOCK_SKILL30, IDC_CHECK_UNLOCK_SKILL31, IDC_CHECK_UNLOCK_SKILL32, IDC_CHECK_UNLOCK_SKILL33, IDC_CHECK_UNLOCK_SKILL34, IDC_CHECK_UNLOCK_SKILL35, IDC_CHECK_UNLOCK_SKILL36, IDC_CHECK_UNLOCK_SKILL37, IDC_CHECK_UNLOCK_SKILL38, IDC_CHECK_UNLOCK_SKILL39, IDC_CHECK_UNLOCK_SKILL40, IDC_CHECK_UNLOCK_SKILL41, IDC_CHECK_UNLOCK_SKILL42, IDC_CHECK_UNLOCK_SKILL43, IDC_CHECK_UNLOCK_SKILL44, IDC_CHECK_UNLOCK_SKILL45, IDC_CHECK_UNLOCK_SKILL46, IDC_CHECK_UNLOCK_SKILL47, IDC_CHECK_UNLOCK_SKILL48, IDC_CHECK_UNLOCK_SKILL49, IDC_CHECK_UNLOCK_SKILL50, IDC_CHECK_UNLOCK_SKILL51, IDC_CHECK_UNLOCK_SKILL52, IDC_CHECK_UNLOCK_SKILL53, IDC_CHECK_UNLOCK_SKILL54, IDC_CHECK_UNLOCK_SKILL55, IDC_CHECK_UNLOCK_SKILL56, IDC_CHECK_UNLOCK_SKILL57, IDC_CHECK_UNLOCK_SKILL58, IDC_CHECK_UNLOCK_SKILL59, IDC_CHECK_UNLOCK_SKILL60, IDC_CHECK_UNLOCK_SKILL61, IDC_CHECK_UNLOCK_SKILL62, IDC_CHECK_UNLOCK_SKILL63, IDC_CHECK_UNLOCK_SKILL64, IDC_CHECK_UNLOCK_SKILL65, IDC_CHECK_UNLOCK_SKILL66, IDC_CHECK_UNLOCK_SKILL67, IDC_CHECK_UNLOCK_SKILL68, IDC_CHECK_UNLOCK_SKILL69, IDC_CHECK_UNLOCK_SKILL70, IDC_CHECK_UNLOCK_SKILL71, IDC_CHECK_UNLOCK_SKILL72, IDC_CHECK_UNLOCK_SKILL73, IDC_CHECK_UNLOCK_SKILL74, IDC_CHECK_UNLOCK_SKILL75, IDC_CHECK_UNLOCK_SKILL76, IDC_CHECK_UNLOCK_SKILL77, IDC_CHECK_UNLOCK_SKILL78, IDC_CHECK_UNLOCK_SKILL79, IDC_CHECK_UNLOCK_SKILL80, IDC_CHECK_UNLOCK_SKILL81, IDC_CHECK_UNLOCK_SKILL82, IDC_CHECK_UNLOCK_SKILL83, IDC_CHECK_UNLOCK_SKILL84, IDC_CHECK_UNLOCK_SKILL85, IDC_CHECK_UNLOCK_SKILL86, IDC_CHECK_UNLOCK_SKILL87, IDC_CHECK_UNLOCK_SKILL88, IDC_CHECK_UNLOCK_SKILL89, IDC_CHECK_UNLOCK_SKILL90, IDC_CHECK_UNLOCK_SKILL91, IDC_CHECK_UNLOCK_SKILL92, IDC_CHECK_UNLOCK_SKILL93, IDC_CHECK_UNLOCK_SKILL94, IDC_CHECK_UNLOCK_SKILL95, IDC_CHECK_UNLOCK_SKILL96, IDC_CHECK_UNLOCK_SKILL97, IDC_CHECK_UNLOCK_SKILL98, IDC_CHECK_UNLOCK_SKILL99, IDC_CHECK_UNLOCK_SKILL100, IDC_CHECK_UNLOCK_SKILL101, IDC_CHECK_UNLOCK_SKILL102, IDC_CHECK_UNLOCK_SKILL103, IDC_CHECK_UNLOCK_SKILL104, IDC_CHECK_UNLOCK_SKILL105, IDC_CHECK_UNLOCK_SKILL106, IDC_CHECK_UNLOCK_SKILL107, IDC_CHECK_UNLOCK_SKILL108, IDC_CHECK_UNLOCK_SKILL109, IDC_CHECK_UNLOCK_SKILL110, IDC_CHECK_UNLOCK_SKILL111, IDC_CHECK_UNLOCK_SKILL112, IDC_CHECK_UNLOCK_SKILL113, IDC_CHECK_UNLOCK_SKILL114, IDC_CHECK_UNLOCK_SKILL115, IDC_CHECK_UNLOCK_SKILL116, IDC_CHECK_UNLOCK_SKILL117, IDC_CHECK_UNLOCK_SKILL118, IDC_CHECK_UNLOCK_SKILL119, IDC_CHECK_UNLOCK_SKILL120, IDC_CHECK_UNLOCK_SKILL121, IDC_CHECK_UNLOCK_SKILL122, IDC_CHECK_UNLOCK_SKILL123, IDC_CHECK_UNLOCK_SKILL124, IDC_CHECK_UNLOCK_SKILL125, IDC_CHECK_UNLOCK_SKILL126, IDC_CHECK_UNLOCK_SKILL127, IDC_CHECK_UNLOCK_SKILL128, IDC_CHECK_UNLOCK_SKILL129, IDC_CHECK_UNLOCK_SKILL130, IDC_CHECK_UNLOCK_SKILL131, IDC_CHECK_UNLOCK_SKILL132, IDC_CHECK_UNLOCK_SKILL133, IDC_CHECK_UNLOCK_SKILL134, IDC_CHECK_UNLOCK_SKILL135, IDC_CHECK_UNLOCK_SKILL136, IDC_CHECK_UNLOCK_SKILL137, IDC_CHECK_UNLOCK_SKILL138, IDC_CHECK_UNLOCK_SKILL139, IDC_CHECK_UNLOCK_SKILL140, IDC_CHECK_UNLOCK_SKILL141, IDC_CHECK_UNLOCK_SKILL142, IDC_CHECK_UNLOCK_SKILL143, IDC_CHECK_UNLOCK_SKILL144, IDC_CHECK_UNLOCK_SKILL145, IDC_CHECK_UNLOCK_SKILL146, IDC_CHECK_UNLOCK_SKILL147, IDC_CHECK_UNLOCK_SKILL148, IDC_CHECK_UNLOCK_SKILL149, IDC_CHECK_UNLOCK_SKILL150, IDC_CHECK_UNLOCK_SKILL151, IDC_CHECK_UNLOCK_SKILL152, IDC_CHECK_UNLOCK_SKILL153, IDC_CHECK_UNLOCK_SKILL154, IDC_CHECK_UNLOCK_SKILL155, IDC_CHECK_UNLOCK_SKILL156, IDC_CHECK_UNLOCK_SKILL157, IDC_CHECK_UNLOCK_SKILL158, IDC_CHECK_UNLOCK_SKILL159, IDC_CHECK_UNLOCK_SKILL160, IDC_CHECK_UNLOCK_SKILL161, IDC_CHECK_UNLOCK_SKILL162, IDC_CHECK_UNLOCK_SKILL163, IDC_CHECK_UNLOCK_SKILL164, IDC_CHECK_UNLOCK_SKILL165, IDC_CHECK_UNLOCK_SKILL166, IDC_CHECK_UNLOCK_SKILL167, IDC_CHECK_UNLOCK_SKILL168, IDC_CHECK_UNLOCK_SKILL169, IDC_CHECK_UNLOCK_SKILL170, IDC_CHECK_UNLOCK_SKILL171, IDC_CHECK_UNLOCK_SKILL172, IDC_CHECK_UNLOCK_SKILL173, IDC_CHECK_UNLOCK_SKILL174, IDC_CHECK_UNLOCK_SKILL175, IDC_CHECK_UNLOCK_SKILL176, IDC_CHECK_UNLOCK_SKILL177, IDC_CHECK_UNLOCK_SKILL178, IDC_CHECK_UNLOCK_SKILL179, IDC_CHECK_UNLOCK_SKILL180, IDC_CHECK_UNLOCK_SKILL181, IDC_CHECK_UNLOCK_SKILL182, IDC_CHECK_UNLOCK_SKILL183, IDC_CHECK_UNLOCK_SKILL184, IDC_CHECK_UNLOCK_SKILL185, IDC_CHECK_UNLOCK_SKILL186, IDC_CHECK_UNLOCK_SKILL187, IDC_CHECK_UNLOCK_SKILL188, IDC_CHECK_UNLOCK_SKILL189, IDC_CHECK_UNLOCK_SKILL190, IDC_CHECK_UNLOCK_SKILL191, IDC_CHECK_UNLOCK_SKILL192 };
const int IDC_SLIDER_SKILL[]		= { IDC_SLIDER_SKILL1, IDC_SLIDER_SKILL2, IDC_SLIDER_SKILL3, IDC_SLIDER_SKILL4, IDC_SLIDER_SKILL5, IDC_SLIDER_SKILL6, IDC_SLIDER_SKILL7, IDC_SLIDER_SKILL8, IDC_SLIDER_SKILL9, IDC_SLIDER_SKILL10, IDC_SLIDER_SKILL11, IDC_SLIDER_SKILL12, IDC_SLIDER_SKILL13, IDC_SLIDER_SKILL14, IDC_SLIDER_SKILL15, IDC_SLIDER_SKILL16, IDC_SLIDER_SKILL17, IDC_SLIDER_SKILL18, IDC_SLIDER_SKILL19, IDC_SLIDER_SKILL20, IDC_SLIDER_SKILL21, IDC_SLIDER_SKILL22, IDC_SLIDER_SKILL23, IDC_SLIDER_SKILL24, IDC_SLIDER_SKILL25, IDC_SLIDER_SKILL26, IDC_SLIDER_SKILL27, IDC_SLIDER_SKILL28, IDC_SLIDER_SKILL29, IDC_SLIDER_SKILL30, IDC_SLIDER_SKILL31, IDC_SLIDER_SKILL32, IDC_SLIDER_SKILL33, IDC_SLIDER_SKILL34, IDC_SLIDER_SKILL35, IDC_SLIDER_SKILL36, IDC_SLIDER_SKILL37, IDC_SLIDER_SKILL38, IDC_SLIDER_SKILL39, IDC_SLIDER_SKILL40, IDC_SLIDER_SKILL41, IDC_SLIDER_SKILL42, IDC_SLIDER_SKILL43, IDC_SLIDER_SKILL44, IDC_SLIDER_SKILL45, IDC_SLIDER_SKILL46, IDC_SLIDER_SKILL47, IDC_SLIDER_SKILL48, IDC_SLIDER_SKILL49, IDC_SLIDER_SKILL50, IDC_SLIDER_SKILL51, IDC_SLIDER_SKILL52, IDC_SLIDER_SKILL53, IDC_SLIDER_SKILL54, IDC_SLIDER_SKILL55, IDC_SLIDER_SKILL56, IDC_SLIDER_SKILL57, IDC_SLIDER_SKILL58, IDC_SLIDER_SKILL59, IDC_SLIDER_SKILL60, IDC_SLIDER_SKILL61, IDC_SLIDER_SKILL62, IDC_SLIDER_SKILL63, IDC_SLIDER_SKILL64, IDC_SLIDER_SKILL65, IDC_SLIDER_SKILL66, IDC_SLIDER_SKILL67, IDC_SLIDER_SKILL68, IDC_SLIDER_SKILL69, IDC_SLIDER_SKILL70, IDC_SLIDER_SKILL71, IDC_SLIDER_SKILL72, IDC_SLIDER_SKILL73, IDC_SLIDER_SKILL74, IDC_SLIDER_SKILL75, IDC_SLIDER_SKILL76, IDC_SLIDER_SKILL77, IDC_SLIDER_SKILL78, IDC_SLIDER_SKILL79, IDC_SLIDER_SKILL80, IDC_SLIDER_SKILL81, IDC_SLIDER_SKILL82, IDC_SLIDER_SKILL83, IDC_SLIDER_SKILL84, IDC_SLIDER_SKILL85, IDC_SLIDER_SKILL86, IDC_SLIDER_SKILL87, IDC_SLIDER_SKILL88, IDC_SLIDER_SKILL89, IDC_SLIDER_SKILL90, IDC_SLIDER_SKILL91, IDC_SLIDER_SKILL92, IDC_SLIDER_SKILL93, IDC_SLIDER_SKILL94, IDC_SLIDER_SKILL95, IDC_SLIDER_SKILL96, IDC_SLIDER_SKILL97, IDC_SLIDER_SKILL98, IDC_SLIDER_SKILL99, IDC_SLIDER_SKILL100, IDC_SLIDER_SKILL101, IDC_SLIDER_SKILL102, IDC_SLIDER_SKILL103, IDC_SLIDER_SKILL104, IDC_SLIDER_SKILL105, IDC_SLIDER_SKILL106, IDC_SLIDER_SKILL107, IDC_SLIDER_SKILL108, IDC_SLIDER_SKILL109, IDC_SLIDER_SKILL110, IDC_SLIDER_SKILL111, IDC_SLIDER_SKILL112, IDC_SLIDER_SKILL113, IDC_SLIDER_SKILL114, IDC_SLIDER_SKILL115, IDC_SLIDER_SKILL116, IDC_SLIDER_SKILL117, IDC_SLIDER_SKILL118, IDC_SLIDER_SKILL119, IDC_SLIDER_SKILL120, IDC_SLIDER_SKILL121, IDC_SLIDER_SKILL122, IDC_SLIDER_SKILL123, IDC_SLIDER_SKILL124, IDC_SLIDER_SKILL125, IDC_SLIDER_SKILL126, IDC_SLIDER_SKILL127, IDC_SLIDER_SKILL128, IDC_SLIDER_SKILL129, IDC_SLIDER_SKILL130, IDC_SLIDER_SKILL131, IDC_SLIDER_SKILL132, IDC_SLIDER_SKILL133, IDC_SLIDER_SKILL134, IDC_SLIDER_SKILL135, IDC_SLIDER_SKILL136, IDC_SLIDER_SKILL137, IDC_SLIDER_SKILL138, IDC_SLIDER_SKILL139, IDC_SLIDER_SKILL140, IDC_SLIDER_SKILL141, IDC_SLIDER_SKILL142, IDC_SLIDER_SKILL143, IDC_SLIDER_SKILL144, IDC_SLIDER_SKILL145, IDC_SLIDER_SKILL146, IDC_SLIDER_SKILL147, IDC_SLIDER_SKILL148, IDC_SLIDER_SKILL149, IDC_SLIDER_SKILL150, IDC_SLIDER_SKILL151, IDC_SLIDER_SKILL152, IDC_SLIDER_SKILL153, IDC_SLIDER_SKILL154, IDC_SLIDER_SKILL155, IDC_SLIDER_SKILL156, IDC_SLIDER_SKILL157, IDC_SLIDER_SKILL158, IDC_SLIDER_SKILL159, IDC_SLIDER_SKILL160, IDC_SLIDER_SKILL161, IDC_SLIDER_SKILL162, IDC_SLIDER_SKILL163, IDC_SLIDER_SKILL164, IDC_SLIDER_SKILL165, IDC_SLIDER_SKILL166, IDC_SLIDER_SKILL167, IDC_SLIDER_SKILL168, IDC_SLIDER_SKILL169, IDC_SLIDER_SKILL170, IDC_SLIDER_SKILL171, IDC_SLIDER_SKILL172, IDC_SLIDER_SKILL173, IDC_SLIDER_SKILL174, IDC_SLIDER_SKILL175, IDC_SLIDER_SKILL176, IDC_SLIDER_SKILL177, IDC_SLIDER_SKILL178, IDC_SLIDER_SKILL179, IDC_SLIDER_SKILL180, IDC_SLIDER_SKILL181, IDC_SLIDER_SKILL182, IDC_SLIDER_SKILL183, IDC_SLIDER_SKILL184, IDC_SLIDER_SKILL185, IDC_SLIDER_SKILL186, IDC_SLIDER_SKILL187, IDC_SLIDER_SKILL188, IDC_SLIDER_SKILL189, IDC_SLIDER_SKILL190, IDC_SLIDER_SKILL191, IDC_SLIDER_SKILL192 };
const int IDC_BUTTON_ALL_SKILL[]	= { IDC_BUTTON_ALL_SKILL1, IDC_BUTTON_ALL_SKILL2, IDC_BUTTON_ALL_SKILL3, IDC_BUTTON_ALL_SKILL4, IDC_BUTTON_ALL_SKILL5, IDC_BUTTON_ALL_SKILL6, IDC_BUTTON_ALL_SKILL7, IDC_BUTTON_ALL_SKILL8, IDC_BUTTON_ALL_SKILL9, IDC_BUTTON_ALL_SKILL10, IDC_BUTTON_ALL_SKILL11, IDC_BUTTON_ALL_SKILL12, IDC_BUTTON_ALL_SKILL13, IDC_BUTTON_ALL_SKILL14, IDC_BUTTON_ALL_SKILL15, IDC_BUTTON_ALL_SKILL16, IDC_BUTTON_ALL_SKILL17, IDC_BUTTON_ALL_SKILL18, IDC_BUTTON_ALL_SKILL19, IDC_BUTTON_ALL_SKILL20, IDC_BUTTON_ALL_SKILL21, IDC_BUTTON_ALL_SKILL22, IDC_BUTTON_ALL_SKILL23, IDC_BUTTON_ALL_SKILL24, IDC_BUTTON_ALL_SKILL25, IDC_BUTTON_ALL_SKILL26, IDC_BUTTON_ALL_SKILL27, IDC_BUTTON_ALL_SKILL28, IDC_BUTTON_ALL_SKILL29, IDC_BUTTON_ALL_SKILL30, IDC_BUTTON_ALL_SKILL31, IDC_BUTTON_ALL_SKILL32, IDC_BUTTON_ALL_SKILL33, IDC_BUTTON_ALL_SKILL34, IDC_BUTTON_ALL_SKILL35, IDC_BUTTON_ALL_SKILL36, IDC_BUTTON_ALL_SKILL37, IDC_BUTTON_ALL_SKILL38, IDC_BUTTON_ALL_SKILL39, IDC_BUTTON_ALL_SKILL40, IDC_BUTTON_ALL_SKILL41, IDC_BUTTON_ALL_SKILL42, IDC_BUTTON_ALL_SKILL43, IDC_BUTTON_ALL_SKILL44, IDC_BUTTON_ALL_SKILL45, IDC_BUTTON_ALL_SKILL46, IDC_BUTTON_ALL_SKILL47, IDC_BUTTON_ALL_SKILL48, IDC_BUTTON_ALL_SKILL49, IDC_BUTTON_ALL_SKILL50, IDC_BUTTON_ALL_SKILL51, IDC_BUTTON_ALL_SKILL52, IDC_BUTTON_ALL_SKILL53, IDC_BUTTON_ALL_SKILL54, IDC_BUTTON_ALL_SKILL55, IDC_BUTTON_ALL_SKILL56, IDC_BUTTON_ALL_SKILL57, IDC_BUTTON_ALL_SKILL58, IDC_BUTTON_ALL_SKILL59, IDC_BUTTON_ALL_SKILL60, IDC_BUTTON_ALL_SKILL61, IDC_BUTTON_ALL_SKILL62, IDC_BUTTON_ALL_SKILL63, IDC_BUTTON_ALL_SKILL64, IDC_BUTTON_ALL_SKILL65, IDC_BUTTON_ALL_SKILL66, IDC_BUTTON_ALL_SKILL67, IDC_BUTTON_ALL_SKILL68, IDC_BUTTON_ALL_SKILL69, IDC_BUTTON_ALL_SKILL70, IDC_BUTTON_ALL_SKILL71, IDC_BUTTON_ALL_SKILL72, IDC_BUTTON_ALL_SKILL73, IDC_BUTTON_ALL_SKILL74, IDC_BUTTON_ALL_SKILL75, IDC_BUTTON_ALL_SKILL76, IDC_BUTTON_ALL_SKILL77, IDC_BUTTON_ALL_SKILL78, IDC_BUTTON_ALL_SKILL79, IDC_BUTTON_ALL_SKILL80, IDC_BUTTON_ALL_SKILL81, IDC_BUTTON_ALL_SKILL82, IDC_BUTTON_ALL_SKILL83, IDC_BUTTON_ALL_SKILL84, IDC_BUTTON_ALL_SKILL85, IDC_BUTTON_ALL_SKILL86, IDC_BUTTON_ALL_SKILL87, IDC_BUTTON_ALL_SKILL88, IDC_BUTTON_ALL_SKILL89, IDC_BUTTON_ALL_SKILL90, IDC_BUTTON_ALL_SKILL91, IDC_BUTTON_ALL_SKILL92, IDC_BUTTON_ALL_SKILL93, IDC_BUTTON_ALL_SKILL94, IDC_BUTTON_ALL_SKILL95, IDC_BUTTON_ALL_SKILL96, IDC_BUTTON_ALL_SKILL97, IDC_BUTTON_ALL_SKILL98, IDC_BUTTON_ALL_SKILL99, IDC_BUTTON_ALL_SKILL100, IDC_BUTTON_ALL_SKILL101, IDC_BUTTON_ALL_SKILL102, IDC_BUTTON_ALL_SKILL103, IDC_BUTTON_ALL_SKILL104, IDC_BUTTON_ALL_SKILL105, IDC_BUTTON_ALL_SKILL106, IDC_BUTTON_ALL_SKILL107, IDC_BUTTON_ALL_SKILL108, IDC_BUTTON_ALL_SKILL109, IDC_BUTTON_ALL_SKILL110, IDC_BUTTON_ALL_SKILL111, IDC_BUTTON_ALL_SKILL112, IDC_BUTTON_ALL_SKILL113, IDC_BUTTON_ALL_SKILL114, IDC_BUTTON_ALL_SKILL115, IDC_BUTTON_ALL_SKILL116, IDC_BUTTON_ALL_SKILL117, IDC_BUTTON_ALL_SKILL118, IDC_BUTTON_ALL_SKILL119, IDC_BUTTON_ALL_SKILL120, IDC_BUTTON_ALL_SKILL121, IDC_BUTTON_ALL_SKILL122, IDC_BUTTON_ALL_SKILL123, IDC_BUTTON_ALL_SKILL124, IDC_BUTTON_ALL_SKILL125, IDC_BUTTON_ALL_SKILL126, IDC_BUTTON_ALL_SKILL127, IDC_BUTTON_ALL_SKILL128, IDC_BUTTON_ALL_SKILL129, IDC_BUTTON_ALL_SKILL130, IDC_BUTTON_ALL_SKILL131, IDC_BUTTON_ALL_SKILL132, IDC_BUTTON_ALL_SKILL133, IDC_BUTTON_ALL_SKILL134, IDC_BUTTON_ALL_SKILL135, IDC_BUTTON_ALL_SKILL136, IDC_BUTTON_ALL_SKILL137, IDC_BUTTON_ALL_SKILL138, IDC_BUTTON_ALL_SKILL139, IDC_BUTTON_ALL_SKILL140, IDC_BUTTON_ALL_SKILL141, IDC_BUTTON_ALL_SKILL142, IDC_BUTTON_ALL_SKILL143, IDC_BUTTON_ALL_SKILL144, IDC_BUTTON_ALL_SKILL145, IDC_BUTTON_ALL_SKILL146, IDC_BUTTON_ALL_SKILL147, IDC_BUTTON_ALL_SKILL148, IDC_BUTTON_ALL_SKILL149, IDC_BUTTON_ALL_SKILL150, IDC_BUTTON_ALL_SKILL151, IDC_BUTTON_ALL_SKILL152, IDC_BUTTON_ALL_SKILL153, IDC_BUTTON_ALL_SKILL154, IDC_BUTTON_ALL_SKILL155, IDC_BUTTON_ALL_SKILL156, IDC_BUTTON_ALL_SKILL157, IDC_BUTTON_ALL_SKILL158, IDC_BUTTON_ALL_SKILL159, IDC_BUTTON_ALL_SKILL160, IDC_BUTTON_ALL_SKILL161, IDC_BUTTON_ALL_SKILL162, IDC_BUTTON_ALL_SKILL163, IDC_BUTTON_ALL_SKILL164, IDC_BUTTON_ALL_SKILL165, IDC_BUTTON_ALL_SKILL166, IDC_BUTTON_ALL_SKILL167, IDC_BUTTON_ALL_SKILL168, IDC_BUTTON_ALL_SKILL169, IDC_BUTTON_ALL_SKILL170, IDC_BUTTON_ALL_SKILL171, IDC_BUTTON_ALL_SKILL172, IDC_BUTTON_ALL_SKILL173, IDC_BUTTON_ALL_SKILL174, IDC_BUTTON_ALL_SKILL175, IDC_BUTTON_ALL_SKILL176, IDC_BUTTON_ALL_SKILL177, IDC_BUTTON_ALL_SKILL178, IDC_BUTTON_ALL_SKILL179, IDC_BUTTON_ALL_SKILL180, IDC_BUTTON_ALL_SKILL181, IDC_BUTTON_ALL_SKILL182, IDC_BUTTON_ALL_SKILL183, IDC_BUTTON_ALL_SKILL184, IDC_BUTTON_ALL_SKILL185, IDC_BUTTON_ALL_SKILL186, IDC_BUTTON_ALL_SKILL187, IDC_BUTTON_ALL_SKILL188, IDC_BUTTON_ALL_SKILL189, IDC_BUTTON_ALL_SKILL190, IDC_BUTTON_ALL_SKILL191, IDC_BUTTON_ALL_SKILL192 };
const int IDC_PROGRESS_SKILL[]		= { IDC_PROGRESS_SKILL1, IDC_PROGRESS_SKILL2, IDC_PROGRESS_SKILL3, IDC_PROGRESS_SKILL4, IDC_PROGRESS_SKILL5, IDC_PROGRESS_SKILL6, IDC_PROGRESS_SKILL7, IDC_PROGRESS_SKILL8, IDC_PROGRESS_SKILL9, IDC_PROGRESS_SKILL10, IDC_PROGRESS_SKILL11, IDC_PROGRESS_SKILL12, IDC_PROGRESS_SKILL13, IDC_PROGRESS_SKILL14, IDC_PROGRESS_SKILL15, IDC_PROGRESS_SKILL16, IDC_PROGRESS_SKILL17, IDC_PROGRESS_SKILL18, IDC_PROGRESS_SKILL19, IDC_PROGRESS_SKILL20, IDC_PROGRESS_SKILL21, IDC_PROGRESS_SKILL22, IDC_PROGRESS_SKILL23, IDC_PROGRESS_SKILL24, IDC_PROGRESS_SKILL25, IDC_PROGRESS_SKILL26, IDC_PROGRESS_SKILL27, IDC_PROGRESS_SKILL28, IDC_PROGRESS_SKILL29, IDC_PROGRESS_SKILL30, IDC_PROGRESS_SKILL31, IDC_PROGRESS_SKILL32, IDC_PROGRESS_SKILL33, IDC_PROGRESS_SKILL34, IDC_PROGRESS_SKILL35, IDC_PROGRESS_SKILL36, IDC_PROGRESS_SKILL37, IDC_PROGRESS_SKILL38, IDC_PROGRESS_SKILL39, IDC_PROGRESS_SKILL40, IDC_PROGRESS_SKILL41, IDC_PROGRESS_SKILL42, IDC_PROGRESS_SKILL43, IDC_PROGRESS_SKILL44, IDC_PROGRESS_SKILL45, IDC_PROGRESS_SKILL46, IDC_PROGRESS_SKILL47, IDC_PROGRESS_SKILL48, IDC_PROGRESS_SKILL49, IDC_PROGRESS_SKILL50, IDC_PROGRESS_SKILL51, IDC_PROGRESS_SKILL52, IDC_PROGRESS_SKILL53, IDC_PROGRESS_SKILL54, IDC_PROGRESS_SKILL55, IDC_PROGRESS_SKILL56, IDC_PROGRESS_SKILL57, IDC_PROGRESS_SKILL58, IDC_PROGRESS_SKILL59, IDC_PROGRESS_SKILL60, IDC_PROGRESS_SKILL61, IDC_PROGRESS_SKILL62, IDC_PROGRESS_SKILL63, IDC_PROGRESS_SKILL64, IDC_PROGRESS_SKILL65, IDC_PROGRESS_SKILL66, IDC_PROGRESS_SKILL67, IDC_PROGRESS_SKILL68, IDC_PROGRESS_SKILL69, IDC_PROGRESS_SKILL70, IDC_PROGRESS_SKILL71, IDC_PROGRESS_SKILL72, IDC_PROGRESS_SKILL73, IDC_PROGRESS_SKILL74, IDC_PROGRESS_SKILL75, IDC_PROGRESS_SKILL76, IDC_PROGRESS_SKILL77, IDC_PROGRESS_SKILL78, IDC_PROGRESS_SKILL79, IDC_PROGRESS_SKILL80, IDC_PROGRESS_SKILL81, IDC_PROGRESS_SKILL82, IDC_PROGRESS_SKILL83, IDC_PROGRESS_SKILL84, IDC_PROGRESS_SKILL85, IDC_PROGRESS_SKILL86, IDC_PROGRESS_SKILL87, IDC_PROGRESS_SKILL88, IDC_PROGRESS_SKILL89, IDC_PROGRESS_SKILL90, IDC_PROGRESS_SKILL91, IDC_PROGRESS_SKILL92, IDC_PROGRESS_SKILL93, IDC_PROGRESS_SKILL94, IDC_PROGRESS_SKILL95, IDC_PROGRESS_SKILL96, IDC_PROGRESS_SKILL97, IDC_PROGRESS_SKILL98, IDC_PROGRESS_SKILL99, IDC_PROGRESS_SKILL100, IDC_PROGRESS_SKILL101, IDC_PROGRESS_SKILL102, IDC_PROGRESS_SKILL103, IDC_PROGRESS_SKILL104, IDC_PROGRESS_SKILL105, IDC_PROGRESS_SKILL106, IDC_PROGRESS_SKILL107, IDC_PROGRESS_SKILL108, IDC_PROGRESS_SKILL109, IDC_PROGRESS_SKILL110, IDC_PROGRESS_SKILL111, IDC_PROGRESS_SKILL112, IDC_PROGRESS_SKILL113, IDC_PROGRESS_SKILL114, IDC_PROGRESS_SKILL115, IDC_PROGRESS_SKILL116, IDC_PROGRESS_SKILL117, IDC_PROGRESS_SKILL118, IDC_PROGRESS_SKILL119, IDC_PROGRESS_SKILL120, IDC_PROGRESS_SKILL121, IDC_PROGRESS_SKILL122, IDC_PROGRESS_SKILL123, IDC_PROGRESS_SKILL124, IDC_PROGRESS_SKILL125, IDC_PROGRESS_SKILL126, IDC_PROGRESS_SKILL127, IDC_PROGRESS_SKILL128, IDC_PROGRESS_SKILL129, IDC_PROGRESS_SKILL130, IDC_PROGRESS_SKILL131, IDC_PROGRESS_SKILL132, IDC_PROGRESS_SKILL133, IDC_PROGRESS_SKILL134, IDC_PROGRESS_SKILL135, IDC_PROGRESS_SKILL136, IDC_PROGRESS_SKILL137, IDC_PROGRESS_SKILL138, IDC_PROGRESS_SKILL139, IDC_PROGRESS_SKILL140, IDC_PROGRESS_SKILL141, IDC_PROGRESS_SKILL142, IDC_PROGRESS_SKILL143, IDC_PROGRESS_SKILL144, IDC_PROGRESS_SKILL145, IDC_PROGRESS_SKILL146, IDC_PROGRESS_SKILL147, IDC_PROGRESS_SKILL148, IDC_PROGRESS_SKILL149, IDC_PROGRESS_SKILL150, IDC_PROGRESS_SKILL151, IDC_PROGRESS_SKILL152, IDC_PROGRESS_SKILL153, IDC_PROGRESS_SKILL154, IDC_PROGRESS_SKILL155, IDC_PROGRESS_SKILL156, IDC_PROGRESS_SKILL157, IDC_PROGRESS_SKILL158, IDC_PROGRESS_SKILL159, IDC_PROGRESS_SKILL160, IDC_PROGRESS_SKILL161, IDC_PROGRESS_SKILL162, IDC_PROGRESS_SKILL163, IDC_PROGRESS_SKILL164, IDC_PROGRESS_SKILL165, IDC_PROGRESS_SKILL166, IDC_PROGRESS_SKILL167, IDC_PROGRESS_SKILL168, IDC_PROGRESS_SKILL169, IDC_PROGRESS_SKILL170, IDC_PROGRESS_SKILL171, IDC_PROGRESS_SKILL172, IDC_PROGRESS_SKILL173, IDC_PROGRESS_SKILL174, IDC_PROGRESS_SKILL175, IDC_PROGRESS_SKILL176, IDC_PROGRESS_SKILL177, IDC_PROGRESS_SKILL178, IDC_PROGRESS_SKILL179, IDC_PROGRESS_SKILL180, IDC_PROGRESS_SKILL181, IDC_PROGRESS_SKILL182, IDC_PROGRESS_SKILL183, IDC_PROGRESS_SKILL184, IDC_PROGRESS_SKILL185, IDC_PROGRESS_SKILL186, IDC_PROGRESS_SKILL187, IDC_PROGRESS_SKILL188, IDC_PROGRESS_SKILL189, IDC_PROGRESS_SKILL190, IDC_PROGRESS_SKILL191, IDC_PROGRESS_SKILL192 };

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkillPanelDlg, CDialog)

BEGIN_MESSAGE_MAP(CSkillPanelDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_ANY_ITEM_CLICKED()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

CSkillPanelDlg::CSkillPanelDlg(CWnd *pParent) : CDialog(IDD_DQMJSE_MONSTER_PANEL, pParent)
{
	m_nCtrlBorder = 0;
	m_nCtrlHeight = 0;
	m_nCtrlSpacing = 0;
	m_eFilter = FILTER_ALL;

	::ZeroMemory(m_unlockCheck, sizeof(m_unlockCheck));
	::ZeroMemory(m_unlockCount, sizeof(m_unlockCount));
	::ZeroMemory(m_skillCount, sizeof(m_skillCount));
	::ZeroMemory(m_skillsetToIndex, sizeof(m_skillsetToIndex));
	::ZeroMemory(m_indexToSkillset, sizeof(m_indexToSkillset));
}

//////////////////////////////////////////////////////////////////////////

int CSkillPanelDlg::GetSkillsetUnlockNum(int skillset) const
{
	if ((skillset < 0) || (skillset >= DQMJ_SKILLSETLIST_LEN))
		return DQMJ_SKILL_LOCKED;

	if (m_unlockCheck[skillset] != BST_CHECKED)
		return DQMJ_SKILL_LOCKED;

	return m_unlockCount[skillset];
}

BOOL CSkillPanelDlg::SetFilter(FILTER filter)
{
	if (m_eFilter == filter)
		return FALSE;

	m_eFilter = filter;
	UpdateData(TRUE);
	RefreshFilter();

	return TRUE;
}

void CSkillPanelDlg::OpenAll()
{
	UpdateData(TRUE);

	for (int i = 0; i < DQMJ_SKILLSETLIST_LEN; i++)
	{
		m_unlockCheck[i] = BST_CHECKED;
		m_unlockCount[i] = m_skillCount[i];

		UpdateSkillset(i);
	}

	UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////////

void CSkillPanelDlg::DoDataExchange(CDataExchange *pDX)
{
	for (int i = 0; i < DQMJ_SKILLSETLIST_LEN; i++)
	{
		int idx = m_skillsetToIndex[i];
		if (idx < 0)
			continue;

		::DDX_Check(pDX, IDC_CHECK_UNLOCK_SKILL[idx], m_unlockCheck[i]);
		::DDX_Slider(pDX, IDC_SLIDER_SKILL[idx], m_unlockCount[i]);
	}

	CDialog::DoDataExchange(pDX);
}

BOOL CSkillPanelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect1, rect2;
	GetDlgItem(IDC_LIBRARY_SKILL1)->GetWindowRect(rect1);
	ScreenToClient(rect1);
	m_nCtrlBorder = rect1.top;
	m_nCtrlHeight = rect1.Height();
	GetDlgItem(IDC_LIBRARY_SKILL1)->GetWindowRect(rect1);
	GetDlgItem(IDC_LIBRARY_SKILL2)->GetWindowRect(rect2);
	m_nCtrlSpacing = rect2.top - rect1.top - m_nCtrlHeight;

	DQMJ_SAVE_LIBRARY_INFO libraryinfo;
	VERIFY(::DQMJSaveQueryLibraryInfo(theApp.GetSaveHandle(), &libraryinfo));

	for (int i = 0; i < DQMJ_SKILLSETLIST_LEN; i++)
	{
		int ss = libraryinfo.skill[i];
		if (ss == DQMJ_SKILL_LOCKED)
		{
			m_unlockCheck[i] = BST_UNCHECKED;
			m_unlockCount[i] = 0;
		}
		else
		{
			m_unlockCheck[i] = BST_CHECKED;
			m_unlockCount[i] = libraryinfo.skill[i];
		}
	}

	RefreshFilter();
	return TRUE;
}

void CSkillPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_PAGE;
	si.nPage = cy;
	SetScrollInfo(SB_VERT, &si, FALSE);
}

void CSkillPanelDlg::OnSetFocus(CWnd *pOldWnd)
{
	// Never catch focus
}

void CSkillPanelDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	if ((pScrollBar != NULL) && ((nSBCode == SB_PAGELEFT) || (nSBCode == SB_PAGERIGHT) || (nSBCode == SB_THUMBTRACK)))
	{
		int id = pScrollBar->GetDlgCtrlID();

		for (int i = 0; i < _countof(IDC_SLIDER_SKILL); i++)
		{
			if (IDC_SLIDER_SKILL[i] != id)
				continue;

			int ss = m_indexToSkillset[i];
			if (ss <= 0)
				continue;

			UpdateData(TRUE);
			UpdateSkillset(ss);
			break;
		}
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSkillPanelDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	if (pScrollBar == NULL)
	{
		SCROLLINFO si;
		GetScrollInfo(SB_VERT, &si, SIF_ALL);

		int pos = si.nPos;
		switch (nSBCode)
		{
		case SB_TOP:
			pos = si.nMin;
			break;
		case SB_BOTTOM:
			pos = si.nMax - si.nPage;
			break;
		case SB_LINEUP:
			pos -= 22;
			break;
		case SB_LINEDOWN:
			pos += 22;
			break;
		case SB_PAGEUP:
			pos -= si.nPage;
			break;
		case SB_PAGEDOWN:
			pos += si.nPage;
			break;
		case SB_THUMBTRACK:
			pos = si.nTrackPos;
			break;
		}

		if (pos >= si.nMax - (int)si.nPage)
			pos = si.nMax - si.nPage;
		if (pos < si.nMin)
			pos = si.nMin;

		if (pos != si.nPos)
		{
			ScrollWindow(0, si.nPos - pos);
			SetScrollPos(SB_VERT, pos);
		}

		SetFocus();
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CSkillPanelDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	CDialog::OnLButtonDown(nFlags, point);
}

void CSkillPanelDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	CDialog::OnRButtonDown(nFlags, point);
}

BOOL CSkillPanelDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (((nFlags & (MK_CONTROL | MK_SHIFT)) == 0) && (zDelta != 0))
	{
		SCROLLINFO si;
		GetScrollInfo(SB_VERT, &si, SIF_ALL);

		int pos = si.nPos - zDelta / 3;

		if (pos >= si.nMax - (int)si.nPage)
			pos = si.nMax - si.nPage;
		if (pos < si.nMin)
			pos = si.nMin;

		if (pos != si.nPos)
		{
			ScrollWindow(0, si.nPos - pos);
			SetScrollPos(SB_VERT, pos);
		}
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

//////////////////////////////////////////////////////////////////////////

void CSkillPanelDlg::RefreshFilter()
{
	int cnt = 0;

	for (int i = 0; i < DQMJ_SKILLSETLIST_LEN; i++)
	{
		m_skillsetToIndex[i] = -1;

		DQMJ_SAVE_SKILLSET_SETTING sss;
		if (!::DQMJSaveGetSkillsetSetting(i, &sss))
			continue;

		switch (m_eFilter)
		{
		case FILTER_SKILL:
			if (sss.param)
				continue;
			break;
		case FILTER_PARAMETER:
			if (!sss.param)
				continue;
			break;
		}

		m_skillCount[i] = sss.count;
		m_skillsetToIndex[i] = cnt;
		m_indexToSkillset[cnt] = i;

		GetDlgItem(IDC_LIBRARY_SKILL[cnt])->ShowWindow(SW_SHOWNOACTIVATE);
		GetDlgItem(IDC_CHECK_UNLOCK_SKILL[cnt])->ShowWindow(SW_SHOWNOACTIVATE);
		GetDlgItem(IDC_SLIDER_SKILL[cnt])->ShowWindow(SW_SHOWNOACTIVATE);
		GetDlgItem(IDC_BUTTON_ALL_SKILL[cnt])->ShowWindow(SW_SHOWNOACTIVATE);
		GetDlgItem(IDC_PROGRESS_SKILL[cnt])->ShowWindow(SW_SHOWNOACTIVATE);

		SetDlgItemText(IDC_LIBRARY_SKILL[cnt], sss.name);
		((CSliderCtrl *)GetDlgItem(IDC_SLIDER_SKILL[cnt]))->SetRange(0, sss.count);

		UpdateSkillset(i);

		cnt++;
	}

	for (int i = cnt; i < _countof(IDC_LIBRARY_SKILL); i++)
	{
		m_indexToSkillset[i] = 0;

		GetDlgItem(IDC_LIBRARY_SKILL[i])->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_UNLOCK_SKILL[i])->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER_SKILL[i])->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_ALL_SKILL[i])->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PROGRESS_SKILL[i])->ShowWindow(SW_HIDE);
	}

	ScrollWindow(0, GetScrollPos(SB_VERT));

	SetScrollRange(SB_VERT, 0, cnt * m_nCtrlHeight + (cnt - 1) * m_nCtrlSpacing + m_nCtrlBorder * 2, FALSE);
	SetScrollPos(SB_VERT, 0, TRUE);

	UpdateData(FALSE);
}

void CSkillPanelDlg::UpdateSkillset(int skillset)
{
	int idx = m_skillsetToIndex[skillset];
	if (idx < 0)
		return;

	int count = m_skillCount[skillset];

	if (m_unlockCheck[skillset] == BST_CHECKED)
	{
		GetDlgItem(IDC_SLIDER_SKILL[idx])->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ALL_SKILL[idx])->EnableWindow(m_unlockCount[skillset] < count);
	}
	else
	{
		GetDlgItem(IDC_SLIDER_SKILL[idx])->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ALL_SKILL[idx])->EnableWindow(TRUE);
	}

	SetDlgItemText(IDC_PROGRESS_SKILL[idx], theApp.GetDecimalString(min(m_unlockCount[skillset], count), count));
}

void CSkillPanelDlg::CheckUnlock(int skillset)
{
	ASSERT((skillset >= 0) && (skillset < DQMJ_SKILLSETLIST_LEN));

	UpdateData(TRUE);
	m_unlockCount[skillset] = 0;
	UpdateSkillset(skillset);
	UpdateData(FALSE);

	((CSkillLibraryDlg *)GetParent())->Update();
}

void CSkillPanelDlg::OpenAllSkill(int skillset)
{
	ASSERT((skillset >= 0) && (skillset < DQMJ_SKILLSETLIST_LEN));

	UpdateData(TRUE);
	m_unlockCheck[skillset] = BST_CHECKED;
	m_unlockCount[skillset] = m_skillCount[skillset];
	UpdateSkillset(skillset);
	UpdateData(FALSE);

	((CSkillLibraryDlg *)GetParent())->Update();
}

//////////////////////////////////////////////////////////////////////////
