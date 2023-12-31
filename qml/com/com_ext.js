/// string
Object.defineProperty(String.prototype, "insert", {
    value: function insert(i, s) {
        return [this.slice(0, i), s, this.slice(i)].join('');
    },
    writable: true,
    configurable: true
});
Object.defineProperty(String.prototype, "del", {
    value: function del(i, len) {
        return [this.slice(0, i), this.slice(i+len)].join('');
    },
    writable: true,
    configurable: true
});
Object.defineProperty(String.prototype, "replaceAt", {
    value: function replaceAt(i, dst) {
        return this.substring(0,i) + dst + (this.length > i+1 ? this.substring(i+1) : '');
    },
    writable: true,
    configurable: true
});
Object.defineProperty(String.prototype, "toArr", {
    value: function toArr(sep) {
        let arr = [];
        let strArr = this.split(sep);
        for(let i = 0; i < strArr.length; i++) {
            if(strArr[i]) {
                arr[arr.length] = strArr[i];
            }
        }
        return arr;
    },
    writable: true,
    configurable: true
});
Object.defineProperty(String.prototype, "reverse", {
    value: function reverse() {
        return this.split('').reverse().join('');
    },
    writable: true,
    configurable: true
});
/// array
Object.defineProperty(Array.prototype, "remove", {
    value: function remove(i) {
        return this.splice(i, 1);
    },
    writable: true,
    configurable: true
});
