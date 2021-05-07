//
// Created by 徐秋实 on 2021/5/7.
//

#ifndef UNHAPPY_EVOLUTION_CODE_SNAPSHOT_SNAP_LINKER_SNAP_LINKER_H_
#define UNHAPPY_EVOLUTION_CODE_SNAPSHOT_SNAP_LINKER_SNAP_LINKER_H_

#include <QString>
#include <unordered_map>

namespace code_snapshot {

class SnapLinker {
  public:
    // 直接使用一个language_type->snap_name->arg_count的符合map来存关系
    std::unordered_map<QString, std::unordered_map<QString, int>> language_snap_map_;

  private:
    static void testQrc();

  public:
    SnapLinker();
    ~SnapLinker();
    int getArgCount(const QString &language_type, const QString &snap_name);
    QStringList getAllLanguageTypes();  // 返回所有的语言类型
    QStringList getAllSnapNamesByLanguageType(const QString &language_type);  // 返回某个语言的所有snap
    QString getRawSnapshot(const QString &language_type, const QString &snap_name);  // 获取原始snap
};
}

#endif //UNHAPPY_EVOLUTION_CODE_SNAPSHOT_SNAP_LINKER_SNAP_LINKER_H_
