## 1.3 (To be decided)
* Update to Sqlite 3.37.0
* Update to wxSqlite3 to main branch
* Support Qt 6
* Tested on following versions:
  - Qt 5.15.2 MSVC2019
  - Qt 6.2.1 MSVC2019

## 1.2 (2018-09-08)
* Add legacy_page_size connection options for all ciphers.

## 1.1 (2018-08-17)

## 1.0 (2018-07-23)
* Update wxSQLite3 to 4.0.4
* Add Qt private configuration in order to use Qt private headers.
* Support multiple ciphers, including AES128CBC, AES256CBC, CHACHA20 and SQLCIPHER.

## 0.7 (2017-04-08)
* Update sqlitecipher plugin debug name pattern on Mac OS.
* Port test code to iOS.

## 0.6 (2017-03-20)
* Fix a crash bug compiling with gcc.
* Update sqlite to 3.17.0
* Update wxSqlite3 to 3.5.2

## 0.5 (2016-05-20)
* Copy private Qt sources to this project.

## 0.4 (2016-05-19)
* Update sqlite to 3.12.2
* Update wxSqlite3 to 3.3.1
* Update driver code to Qt 5.6. Now we could support Qt 5.0 to 5.6, but not for 5.7.
* Improve Qt private path settings.
* Add password create, update and remove. **Thanks to @topillar**
* Return false when password is incorrect.

## 0.3 (2014-09-20)
* Add password paramater to open() function.
* Update sqlite to 3.8.5
* Update wxSqlite3 to 3.1.0

## 0.2 (2013-01-09)
* Update sqlite to 3.7.15.1
* Support for Qt 5

## 0.1 (2012-09-27)
* sqlite 3.7.13