# lts-2.1.2 本地可用性检查

以下检查基于当前仓库状态：

## 分支列表
```
$ git branch -a
* work
```

## 本地 heads
```
$ git show-ref --heads
bede2140fe411095adf78bb27718c2be3a72c469 refs/heads/work
```

## 远程配置
```
$ git remote -v
upstream https://github.com/MarlinFirmware/Marlin.git (fetch)
upstream https://github.com/MarlinFirmware/Marlin.git (push)
```

## 尝试拉取上游 lts-2.1.2
```
$ git fetch upstream lts-2.1.2
fatal: unable to access 'https://github.com/MarlinFirmware/Marlin.git/': CONNECT tunnel failed, response 403
```

结论：当前仓库未发现 `lts-2.1.2` 分支，且从上游拉取仍被环境网络限制阻断（HTTP 403）。
