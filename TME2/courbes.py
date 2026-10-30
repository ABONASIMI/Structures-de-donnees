from pathlib import Path

data = [
    list(map(float, line.split()))
    for line in Path("Vitess.txt").read_text().splitlines()
    if line.strip()
]

svg = ['<svg xmlns="http://www.w3.org/2000/svg" width="850" height="620">']
svg.append('<rect width="100%" height="100%" fill="white"/>')

for k, (col, title, color) in enumerate([
    (1, "Algorithme O(n²)", "red"),
    (2, "Algorithme O(n)", "blue")
]):
    x0, x1 = 100, 780
    y0, y1 = 75 + k * 270, 260 + k * 270
    max_n = max(r[0] for r in data)
    max_t = max(r[col] for r in data) or 1

    points = []
    svg.append(f'<text x="100" y="{y0-20}" font-size="20">{title}</text>')
    svg.append(f'<path d="M{x0},{y0} V{y1} H{x1}" fill="none" stroke="black"/>')

    for r in data:
        x = x0 + (r[0] / max_n) * (x1 - x0)
        y = y1 - (r[col] / max_t) * (y1 - y0)
        points.append(f"{x:.1f},{y:.1f}")
        svg.append(f'<circle cx="{x}" cy="{y}" r="4" fill="{color}"/>')
        svg.append(f'<text x="{x}" y="{y1+18}" font-size="11" text-anchor="middle">{int(r[0])}</text>')

    svg.append(f'<polyline points="{" ".join(points)}" fill="none" stroke="{color}" stroke-width="2"/>')
    svg.append(f'<text x="10" y="{y0+10}" font-size="12">{max_t:.6f} s</text>')
    svg.append(f'<text x="400" y="{y1+40}" font-size="13">Taille du tableau (n)</text>')

svg.append('</svg>')
Path("courbes.svg").write_text("\n".join(svg))
print("Graphique cree : courbes.svg")
