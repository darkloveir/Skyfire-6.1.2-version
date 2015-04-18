CREATE TABLE IF NOT EXISTS `playercreateinfo_cast_spell` (
  `raceMask` int(10) unsigned NOT NULL DEFAULT '0',
  `classMask` int(10) unsigned NOT NULL DEFAULT '0',
  `spell` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `note` varchar(255) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*!40000 ALTER TABLE `playercreateinfo_cast_spell` DISABLE KEYS */;
REPLACE INTO `playercreateinfo_cast_spell` (`raceMask`, `classMask`, `spell`, `note`) VALUES
	(0, 32, 48266, 'Death Knight - Blood Presence'),
	(1, 4, 79597, 'Human - Hunter - Young Wolf'),
	(2, 4, 79598, 'Orc - Hunter - Young Boar'),
	(4, 4, 79593, 'Dwarf - Hunter - Young Bear'),
	(8, 4, 79602, 'Night Elf - Hunter - Young Cat'),
	(16, 4, 79600, 'Undead - Hunter - Young Widow'),
	(32, 4, 79603, 'Tauren - Hunter - Young Tallstrider'),
	(128, 4, 79599, 'Troll - Hunter - Young Raptor'),
	(256, 4, 79595, 'Goblin - Hunter - Young Crab'),
	(512, 4, 79594, 'Blood Elf - Hunter - Young Dragonhawk'),
	(1024, 4, 79601, 'Draenei - Hunter - Young Moth'),
	(2097152, 4, 79596, 'Worgen - Hunter - Young Mastiff'),
	(0, 1, 2457, 'Warrior - Battle Stance'),
	(0, 256, 688, 'Warlock - Summon Imp'),
	(16, 0, 73523, 'Undead - Rigor Mortis');
/*!40000 ALTER TABLE `playercreateinfo_cast_spell` ENABLE KEYS */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
