INSERT INTO `version_db_world` (`sql_rev`) VALUES ('1575126277243796500');

CREATE TABLE IF NOT EXISTS `creature_template_outfits` (
	`entry` INT(10) UNSIGNED NOT NULL,
	`race` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1',
	`gender` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' COMMENT '0 for male, 1 for female',
	`skin` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`face` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`hair` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`haircolor` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`facialhair` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
	`head` INT(10) NOT NULL DEFAULT '0',
	`shoulders` INT(10) NOT NULL DEFAULT '0',
	`body` INT(10) NOT NULL DEFAULT '0',
	`chest` INT(10) NOT NULL DEFAULT '0',
	`waist` INT(10) NOT NULL DEFAULT '0',
	`legs` INT(10) NOT NULL DEFAULT '0',
	`feet` INT(10) NOT NULL DEFAULT '0',
	`wrists` INT(10) NOT NULL DEFAULT '0',
	`hands` INT(10) NOT NULL DEFAULT '0',
	`back` INT(10) NOT NULL DEFAULT '0',
	`tabard` INT(10) NOT NULL DEFAULT '0',
	PRIMARY KEY (`entry`)
)
COMMENT='Use positive values for item entries and negative to use item displayid for head, shoulders etc.'
COLLATE='utf8_general_ci'
ENGINE=InnoDB;

ALTER TABLE `creature_template`
	CHANGE COLUMN `modelid1` `modelid1` INT NOT NULL DEFAULT '0' AFTER `KillCredit2`,
	CHANGE COLUMN `modelid2` `modelid2` INT NOT NULL DEFAULT '0' AFTER `modelid1`,
	CHANGE COLUMN `modelid3` `modelid3` INT NOT NULL DEFAULT '0' AFTER `modelid2`,
	CHANGE COLUMN `modelid4` `modelid4` INT NOT NULL DEFAULT '0' AFTER `modelid3`;

ALTER TABLE `creature_template_outfits`
    ADD COLUMN `class` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1' AFTER `race`;

ALTER TABLE `creature_template_outfits`
	ADD COLUMN `guildid` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `tabard`;

ALTER TABLE `creature_template_outfits`
	COMMENT='Use positive values for item entries and negative to use item displayid for head, shoulders etc.';

ALTER TABLE `creature_template_outfits`
	ADD COLUMN `description` TEXT NULL DEFAULT NULL AFTER `guildid`;

ALTER TABLE `creature_template_outfits`
	ADD COLUMN `npcsoundsid` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'entry from NPCSounds.dbc/db2' AFTER `entry`;

ALTER TABLE `creature_template` CHANGE COLUMN `modelid1` `modelid1` BIGINT;
ALTER TABLE `creature_template` CHANGE COLUMN `modelid2` `modelid2` BIGINT;
ALTER TABLE `creature_template` CHANGE COLUMN `modelid3` `modelid3` BIGINT;
ALTER TABLE `creature_template` CHANGE COLUMN `modelid4` `modelid4` BIGINT;
UPDATE creature_template SET modelid1 = (-modelid1) + 3000000000 WHERE modelid1 < 0;
UPDATE creature_template SET modelid2 = (-modelid2) + 3000000000 WHERE modelid2 < 0;
UPDATE creature_template SET modelid3 = (-modelid3) + 3000000000 WHERE modelid3 < 0;
UPDATE creature_template SET modelid4 = (-modelid4) + 3000000000 WHERE modelid4 < 0;
ALTER TABLE `creature_template` CHANGE COLUMN `modelid1` `modelid1` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `creature_template` CHANGE COLUMN `modelid2` `modelid2` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `creature_template` CHANGE COLUMN `modelid3` `modelid3` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `creature_template` CHANGE COLUMN `modelid4` `modelid4` INT(10) UNSIGNED NOT NULL DEFAULT '0';

ALTER TABLE `creature_template_outfits` DROP PRIMARY KEY;
UPDATE creature_template_outfits SET entry = entry + 3000000000 WHERE entry <= 0x7FFFFFFF;
ALTER TABLE `creature_template_outfits` ADD PRIMARY KEY (`entry`);

ALTER TABLE `creature` CHANGE COLUMN `modelid` `modelid` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `game_event_model_equip` CHANGE COLUMN `modelid` `modelid` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `creature_model_info` CHANGE COLUMN `DisplayID` `DisplayID` INT(10) UNSIGNED NOT NULL DEFAULT '0';
