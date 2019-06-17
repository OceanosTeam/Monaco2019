-- ---------------------------
-- Table structure for gps
-- ---------------------------
CREATE TABLE IF NOT EXISTS `gps` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `Latitude` DECIMAL(8,6) DEFAULT '0',
  `Longitude` DECIMAL(8,6) DEFAULT '0',
  `Time` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  `serverSideName` VARCHAR(15) DEFAULT 'gps',
  PRIMARY KEY (`id`)
);


-- Test values
INSERT INTO `gps` (Latitude, Longitude) VALUES ('43.7366', '7.4284');
INSERT INTO `gps` (Latitude, Longitude) VALUES ('33.2', '35.22');
INSERT INTO `gps` (Latitude, Longitude) VALUES ('33.2', '35.22');
INSERT INTO `gps` (Latitude, Longitude) VALUES ('33.2', '35.22');


