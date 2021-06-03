//
// Created by 徐秋实 on 2021/5/7.
//

#include <QDebug>
#include <QDirIterator>
#include <QString>
#include "snap_linker.h"

code_snapshot::SnapLinker::SnapLinker() {
    // 初始化snap map结构
    this->language_snap_map_ = {
        {QString("python"),
            {
                {
                    QString("name_equal_main"), 0
                },
                {
                    QString("singleton_meta"), 0
                },
                {
                    QString("luigi_build_run"), 0
                }
            }
        },
        {QString("qt"),
            {
                {
                    QString("show_all_qrc"), 0
                }
            }
        },
        {
            QString("command_line"),
            {
                {
                    QString("luigi_run_command"), 0
                }
            }
        }
    };
}

code_snapshot::SnapLinker::~SnapLinker() {
    for (auto first_level: this->language_snap_map_) {
        first_level.second.clear();
    }
    this->language_snap_map_.clear();
}

void code_snapshot::SnapLinker::testQrc() {
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        qDebug() << it.next();
    }
}

QString code_snapshot::SnapLinker::getRawSnapshot(const QString &language_type, const QString &snap_name) {
    // 获取原始snap
    QString file_path = QString(":/code_snapshot/%1/%2.txt").arg(language_type, snap_name);
    QFile file(file_path);
    if (!file.open(QFile::ReadOnly |
        QFile::Text)) {
        qDebug() << " Could not open the file for reading";
        return QString();
    }
    QTextStream in(&file);
    QString raw_snap = in.readAll();
    file.close();
//    qDebug() << raw_snap;
    return raw_snap;
}

int code_snapshot::SnapLinker::getArgCount(const QString &language_type, const QString &snap_name) {
    // 获取snap有多少参数
    if (this->language_snap_map_.find(language_type) == this->language_snap_map_.end()) {
        return 0;
    }
    if (this->language_snap_map_.find(language_type)->second.find(snap_name)
        == this->language_snap_map_.find(language_type)->second.end()) {
        return 0;
    }
    return this->language_snap_map_.find(language_type)->second.find(snap_name)->second;
}

QStringList code_snapshot::SnapLinker::getAllLanguageTypes() {
    // 获取所有的语言列表
    QStringList types = QStringList();
    for (auto &it : this->language_snap_map_) {
        types.push_back(it.first);
    }
    return types;
}

QStringList code_snapshot::SnapLinker::getAllSnapNamesByLanguageType(const QString &language_type) {
    // 获取某一语言的所有snap名字
    QStringList types = QStringList();
    if (this->language_snap_map_.find(language_type) == this->language_snap_map_.end()) {
        return types;
    }
    for (auto &it : this->language_snap_map_.find(language_type)->second) {
        types.push_back(it.first);
    }
    return types;
}

