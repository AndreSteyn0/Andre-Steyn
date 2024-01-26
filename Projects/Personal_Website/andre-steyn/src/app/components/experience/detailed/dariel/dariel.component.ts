import { AfterViewInit, Component } from '@angular/core';
import { Router, RouterLink, RouterLinkActive } from '@angular/router';
import { ScrollService } from '../../../../services/scroll.service';

@Component({
  selector: 'app-dariel',
  standalone: true,
  imports: [RouterLink, RouterLinkActive],
  templateUrl: './dariel.component.html',
  styleUrl: './dariel.component.css',
})
export class DarielComponent implements AfterViewInit {
  constructor(private router: Router, private scrollService: ScrollService) {}

  ngAfterViewInit() {
    this.scrollService.scrollObservable.subscribe((section) => {
      setTimeout(() => {
        this.scrollToElement(section);
      }, 0);
    });
  }

  navigateAndScroll(): void {
    this.scrollService.scrollTo('darielAnchor');
    this.router.navigate(['']);
  }

  scrollToElement(section: string) {
    document.getElementById(section)?.scrollIntoView({ behavior: 'smooth', inline:'start', block: 'start' });
  }
}
