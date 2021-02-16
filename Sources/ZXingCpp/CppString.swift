import Foundation
import CZXingCpp

final class CppString {
    let pointer: OpaquePointer

    init(_ pointer: OpaquePointer) {
        self.pointer = pointer
    }

    deinit {
        cppstring_delete(pointer)
    }

    var rawData: UnsafePointer<CChar> {
        cppstring_data(pointer)
    }

    var size: Int {
        cppstring_size(pointer)
    }

    var data: Data {
        Data(bytes: rawData, count: size)
    }

    func toString() -> String? {
        return String(data: self.data, encoding: .utf8)
    }
}
